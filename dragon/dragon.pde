DragonCurve curve;

void setup() {
  size(800, 600);
  background(0);
  curve = new DragonCurve();
}

void draw() {
  background(0);
  stroke(255);
  curve.draw();
}

void keyPressed() {
  if (key == '+') {
    // go one iteration further in the dragon curve.
    curve.descend();
  } else if (key == '=') {
    // go one iteration back in the dragon curve.
    curve.ascend();
  }
}
