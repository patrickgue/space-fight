#define BYTE unsigned char
#define NUM_SCAN_QUE 256     // this MUST be 256, using BYTE roll-over for
                             // q code


static void interrupt (far *oldkb)(void);   /* BIOS keyboard handler */

// Q code
BYTE gb_scan;
BYTE gb_scan_q[NUM_SCAN_QUE];
BYTE gb_scan_head;
BYTE gb_scan_tail;

/*
   invoked by the hardware keyboard interupt
   ques up the raw scan codes
    stuff raw scan codes into the array gb_scan_q[]
*/
/* ---------------------- get_scan() --------------------- April 17,1993 */
void interrupt get_scan(void);
#param

   /* read the raw scan code from the keyboard */
   asm   cli

   asm   {

         in    al, 060h       /* read scan code */
         mov   gb_scan, al
         in    al, 061h       /* read keyboard status */
         mov   bl, al
         or    al, 080h
         out   061h, al       /* set bit 7 and write */
         mov   al, bl
         out   061h, al       /* write again, bit 7 clear */

         mov   al, 020h       /* reset PIC */
         out   020h, al

         /* end of re-set code */

         sti
         }

// save the raw scan code in a 256 byte buffer
   *(gb_scan_q+gb_scan_tail)=gb_scan;
   ++gb_scan_tail;
}

/*

save the old int9 ISR vector, and install our own
*/
/* ---------------------- init_keyboard() ---------------- April 17,1993 */
void init_keyboard(void)
{
   BYTE far *bios_key_state;

   /* save old BIOS key board handler */
   oldkb=getvect(9);

   // turn off num-lock via BIOS 
   bios_key_state=MK_FP(0x040, 0x017);
   *bios_key_state&=(~(32 | 64));     // toggle off caps lock and
                                      // num lock bits in the BIOS variable
   oldkb();      // call BIOS key handler to change keyboard lights

   gb_scan_head=0;
   gb_scan_tail=0;
   gb_scan=0;

   /* install our own handler */
   setvect(9, get_scan);

}

/* restore the bios keyboard handler */
/* ---------------------- deinit_keyboard() -------------- April 17,1993 */
void deinit_keyboard(void)
{
   setvect(9, oldkb);
}
