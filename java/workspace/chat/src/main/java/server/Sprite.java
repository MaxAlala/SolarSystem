package server;


import javafx.scene.shape.Rectangle;

 class Sprite {
    String address;
    String type = "AI_robot";
    int x = 0;
    int y = 0;


     public int getX() {
         return x;
     }

     public void setX(int x) {
         this.x = x;
     }


     public int getY() {
         return y;
     }

     public void setY(int y) {
         this.y = y;
     }

     public String getDirection() {
        return direction;
    }

    public void setDirection(String direction) {
        this.direction = direction;
    }

    String direction = null; // aswd

    Sprite(String address,int x, int y) {
    setX(x);
    setY(y);
        setAddress(address);
    }

     public String getType() {
         return type;
     }

     public void setType(String type) {
         this.type = type;
     }

     public String getAddress() {
         return address;
     }

     public void setAddress(String address) {
         this.address = address;
     }

}