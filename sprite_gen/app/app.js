let currentColour = 0;

let cursor;
let brush;
let canvas;
let ctx;
let sprite;
let spritesize;
let scale;
let out = "";
var rgbToHex = function (rgb) { 
    var hex = Number(rgb).toString(16);
    if (hex.length < 2) {
         hex = "0" + hex;
    }
    return hex;
  };

  var fullColorHex = function(r,g,b) {   
    var red = rgbToHex(r);
    var green = rgbToHex(g);
    var blue = rgbToHex(b);
    return red+green+blue;
  };

function renderPalette(id) {
    document.querySelector("#colours").innerHTML = "";
    for (let colour of colours) {
        let celm = document.createElement("div");
        celm.classList.add("colour");
        if(colour.colorId == id) {
            celm.classList.add("selected");
        }
        celm.style.backgroundColor = colour.hexString;
        celm.title = "["+colour.colorId+"]";
        celm.addEventListener("click", function () {
            currentColour = colour.colorId;
            renderPalette(colour.colorId);
        });
        document.querySelector("#colours").appendChild(celm);
    }
}


class Vector {
    constructor(_x, _y) {
        this.x = _x;
        this.y = _y;
    };
}







function render() {
    ctx.clearRect(0, 0, spritesize.x *scale, spritesize.y *scale);

    for (let x = 0; x < spritesize.x; x++) {
        for (let y = 0; y < spritesize.y; y++) {
            let c = sprite[(y * spritesize.x) + x];
            if (c == 0xff) {
                ctx.strokeStyle = "#000";
                ctx.fillStyle = "#000000";
                ctx.fillRect(x *scale + 4, y *scale + 4, 2, 2);
            }
            else {
                ctx.strokeStyle = "#fff";
                ctx.fillStyle = colours[c].hexString;
                ctx.fillRect(x *scale, y *scale,scale,scale);
            }
            ctx.lineWidth =1;
            ctx.strokeStyle = "#000";
            if(cursor.x >= x && cursor.x < x + brush.x && cursor.y >= y && cursor.y < y + brush.y) {
                ctx.strokeStyle = "#f00";
                ctx.lineWidth = 2;
            }
            ctx.beginPath();
            ctx.rect(x *scale, y *scale,scale,scale);
            ctx.stroke();

        }
    }
    document.querySelector("#output").value = sprite.join();
}

document.querySelector("#fill").addEventListener("click", function () {
    for (let i = 0; i < 256; i++) {
        sprite[i] = currentColour;
    }
});

document.querySelector("#filltransp").addEventListener("click", function () {
    for (let i = 0; i < 256; i++) {
        if (sprite[i] != 0xff)
            sprite[i] = currentColour;
    }
});

document.querySelector("#parse").addEventListener("click", function () {
    sprite = document.querySelector("#output").value.split(",");
    render();
});

function initSprite() {
    sprite = new Array(spritesize.x * spritesize.y);
    for (let i = 0; i < spritesize.x * spritesize.y; i++) { sprite[i] = 0xff; }
    canvas.width = canvas.style.width = spritesize.x *scale;
    canvas.height = canvas.style.height = spritesize.y *scale;
}

function load() {
    let canvas = document.createElement("canvas");
    canvas.width = 96;
    canvas.height = 40;
    let c = canvas.getContext('2d');
    let image = new Image(96, 40);
    image.src = "test.png";

    spritesize.x = 96;
    spritesize.y = 40;
    spirte = new Array(spritesize.x * spritesize.y);
    
    image.onload = function() {
        c.drawImage(image,0,0);
        
        for(let x = 0; x < 96; x++) {
            for(let y = 0; y < 40; y++) {
                var data = c.getImageData(x, y, 1, 1).data;
                for(let colour of colours) {
                    //console.log(fullColorHex(data[0],data[1],data[2]));
                    if(colour.hexString == fullColorHex(data[0],data[1],data[2])) {
                        //sprite.push(colour.colorId);
                        console.log(colour.colorId)
                    }
                }
            }
        }
        console.log(sprite);
        render();
    }
}

function init() {
    canvas = document.querySelector("#canvas");
    ctx = canvas.getContext('2d');

    scale = 10;
    cursor = new Vector(-1,-1);
    brush = new Vector(1,1);
    spritesize = new Vector(16,16)
    initSprite();
    renderPalette(0);
    render();


    canvas.addEventListener("mousemove", function(e) {
        cursor.x = Math.floor((e.layerX /scale));
        cursor.y = Math.floor((e.layerY /scale));
        if(e.buttons == 1) {
            for(let x = 0; x < spritesize.x; x++) {
                for(let y = 0; y < spritesize.y; y++) {
                    if(cursor.x >= x && cursor.x < x + brush.x && cursor.y >= y && cursor.y < y + brush.y) {
                        sprite[(y * spritesize.x) + x] = currentColour;
                    }
                }
            }
        }
        render();
    });

    canvas.addEventListener("mousedown", function(e) {
        cursor.x = Math.floor((e.layerX /scale));
        cursor.y = Math.floor((e.layerY /scale));
        if(e.buttons == 1) {
            for(let x = 0; x < spritesize.x; x++) {
                for(let y = 0; y < spritesize.y; y++) {
                    if(cursor.x >= x && cursor.x < x + brush.x && cursor.y >= y && cursor.y < y + brush.y) {
                        sprite[(y * spritesize.x) + x] = currentColour;
                    }
                }
            }
        }
        render();
    });

    for(let elm of document.querySelectorAll(".brushset")) {
        elm.addEventListener("change", () => {
            brush.x = Number(document.querySelector("#brushw").value);
            brush.y = Number(document.querySelector("#brushh").value);
            scale = Number(document.querySelector("#scale").value);
            canvas.width = canvas.style.width = spritesize.x *scale;
            canvas.height = canvas.style.height = spritesize.y *scale;
            render();
        })
    }

    for(let elm of document.querySelectorAll(".spriteset")) {
        elm.addEventListener("change", () => {
            spritesize.x = Number(document.querySelector("#width").value);
            spritesize.y = Number(document.querySelector("#height").value);
            initSprite();
        })
    }

}
