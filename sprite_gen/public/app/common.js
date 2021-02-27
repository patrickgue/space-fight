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


class Sprite {
  name;
  width;
  height;
  data;

  constructor(_name, _width, _height, _data) {
    if (typeof _name === 'object') {
      this.name = _name.name;
      this.width = _name.width;
      this.height = _name.height;
      this.data = _name.data;
    } else {
      this.name = _name;
      this.width = _width;
      this.height = _height;
      this.data = _data;
    }
  }
}

class Vector {
  constructor(_x, _y) {
      this.x = _x;
      this.y = _y;
  };
}

if (typeof module !== 'undefined') {
  module.exports = {
    Sprite,
    Vector,
    rgbToHex,
    fullColorHex
  }
}