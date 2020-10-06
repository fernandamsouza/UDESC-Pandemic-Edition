import toxi.physics3d.*;
import toxi.physics3d.behaviors.*;
import toxi.physics3d.constraints.*;
import toxi.geom.*;


int colunas = 40;
int filas = 40;

Particula[][] particulas = new Particula[colunas][filas];
ArrayList<Mola> molas;

float w = 10;

AttractionBehavior3D repulsao = null;

SphereConstraint esfera;
VerletPhysics3D fisica;

void setup() {
  size(600, 600, P3D); 
  molas = new ArrayList<Mola>();

  fisica = new VerletPhysics3D();
  Vec3D gravity = new Vec3D(0, 0.2, 0);
  GravityBehavior3D gb = new GravityBehavior3D(gravity);
  fisica.addBehavior(gb);
  
  //Cria as particulas nas devidas possições. 
  float x = -colunas*w/2;
  for (int i = 0; i < colunas; i++) {
    float z = 0;
    for (int j = 0; j < filas; j++) {
      Particula p = new Particula(x, -200, z);
      particulas[i][j] = p;
      fisica.addParticle(p);
      z = z + w;
    }
    x = x + w;
  }
  
  //Criando as molas entre as particulas
  for (int i = 0; i < colunas; i++) {
    for (int j = 0; j < colunas; j++) {
      Particula a = particulas[i][j];
      if (i != colunas-1) {
        Particula b1 = particulas[i+1][j];
        Mola s1 = new Mola(a, b1);
        molas.add(s1);
        fisica.addSpring(s1);
      }
      if (j != filas-1) {
        Particula b2 = particulas[i][j+1];
        Mola s2 = new Mola(a, b2);
        molas.add(s2);
        fisica.addSpring(s2);
      }
    }
  }
  
  particulas[0][0].lock();
  particulas[colunas-1][0].lock();
}

float a = 0;

void draw() {
  background(51);
  
  translate(width/2, height/2);
  keyPressed();
  
  fisica.update();
  
 
 // MOSTRAR AS PARTICULAS
  for (int i = 0; i < colunas; i++) {
    for (int j = 0; j < filas; j++) {
      particulas[i][j].display();
    }
  }
 /*
 // MOSTRAR MOLAS
  for (Mola s : molas) {
    s.display();
  }
  */
  
  color amarelo = color(255, 204, 0);
  color vermelho = color(255, 0, 0);
  mousePressed();
  mouseReleased();
  translate(mouseX-250,mouseY-250);
  
  if (mousePressed == true)
    fill(amarelo);
  else {
    fill(vermelho);
  }
  noStroke();
  rect(8, 8, 8, 8);
  
}

void mousePressed(){
   repulsao = new AttractionBehavior3D(new Vec3D(mouseX-250,mouseY-250,0),50,-40);
   fisica.addBehavior(repulsao);
}
void mouseReleased(){
  if(repulsao != null) fisica.removeBehavior(repulsao);
}
void keyPressed()
{
  if ( keyCode == LEFT )
  {
    rotateY(a);
    a += 0.01;
  }

  else if ( keyCode == RIGHT )
  {
    rotateY(-a);
    a += 0.01;
  }
  
}
