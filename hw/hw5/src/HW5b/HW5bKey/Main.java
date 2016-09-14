import java.io.*;

class Main {

   public static void main(String args[]) {
      char c = 0;
      short s = 1;
      int i = 2;
      float f = 0.0f;
      double df = 1.0;

      B b = new B( );
      D d = new D( );

      System.out.println("Direct calls");
      // d.foo(d, f); 
      // d.foo(c, d, df);
      d.foo(df); // B:foo(double)
      d.foo(i); // B:foo(float)
      // d.foo( );
      // d.foo(i, d, df);
      d.foo(c, b, f); // B:foo(int, B, float)
      d.foo(f); // B:foo(float)
      d.foo(c); // B:foo(float)
      d.foo(s, d, df); // B:foo(short, B, double)
      // d.foo(i, d);

      System.out.println("b.caller");
      b.caller( );

   }
}
