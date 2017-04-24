public class Line {
  private PVector start;
  private PVector end;

  Line(PVector start, PVector end) {
    this.start = start;
    this.end = end;
  }

  PVector getStart() {
    return start;
  }

  PVector getEnd() {
    return end;
  }

  void draw() {
    line(start.x, start.y, end.x, end.y);
  }
}
