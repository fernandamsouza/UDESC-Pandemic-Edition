class Mola extends VerletSpring3D {

  Mola(Particula a, Particula b) {
    super(a, b, w, 0.8);
  }
  
  void display() {
    stroke(255);
    strokeWeight(2);
    //line(a.x, a.y, a.z, b.x, b.y, b.z);
  } 
}
