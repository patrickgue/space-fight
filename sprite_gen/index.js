const express = require('express');
const bodyParser = require('body-parser');
const fs = require('fs');
const {Sprite} = require('./public/app/common');
const app = express();


const port = 8080;

app.use(express.static('public'));
app.use(bodyParser.json());

app.get('/sprites', (req, res) => {
    let dataPromise = new Promise((resolve) => {
        if (fs.existsSync('data/sprites.json')) {
            fs.readFile('data/sprites.json', (err, data) => {
                resolve(JSON.parse(data).map(d => new Sprite(d)));
            })
        } else {
            fs.writeFile('data/sprite.json', '[]', () => {
                resolve([]);
            })
        }
    
    });
    

    dataPromise.then((data) => {
        res.end(JSON.stringify(data));
    }).catch((err) => {
        res.status(500);
        res.end('Error' + err);
    });
});

app.post('/sprites', (req, res) => {
    fs.writeFile('data/sprite.json', req.body.map(item => new Sprite(item)), (err) => {
        if (err) {
            res.status(500);
        }
        res.end();
    });
});

app.listen(port, () => {
    console.log(`Listening on port ${port}`);
})