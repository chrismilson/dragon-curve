public class DragonCurve {
  private Line[] curve;
  int depth;

  DragonCurve() {
    curve = new Line[1];
    Line first = new Line(new PVector(width/3, height/2),
      new PVector(2* width/3, height/2));

    depth = 0;
    curve[0] = first;
  }

  void descend() {
    if (depth >= 12) return;
    depth++;

    Line[] newCurve = new Line[(int) pow(2, depth)];

    for (int i = 0; i < curve.length; i++) {
      PVector start = curve[i].getStart();
      PVector end = curve[i].getEnd();
      PVector middle = PVector.sub(end, start);
      middle.div(sqrt(2));
      middle.rotate(-QUARTER_PI);

      middle.add(start);

      newCurve[2*i] = new Line(start, middle);
      newCurve[2*i + 1] = new Line(end, middle);
    }

    curve = newCurve;
  }

  void ascend() {
    if (depth == 0) return;
    depth--;

    Line[] newCurve = new Line[(int) pow(2, depth)];

    // since the number of lines is always even when depth > 0 we dont have to
    // worry about going out of bounds.
    for (int i = 0; i < curve.length; i += 2) {
      Line newLine = new Line(curve[i].getStart(), curve[i + 1].getStart());
      newCurve[i/2] = newLine;
    }

    curve = newCurve;
  }

  void draw() {
    for (Line line : curve) {
      line.draw();
    }
  }
}
