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

      System.out.println("Direct calls"); //print direct calls
      //d.foo(d, f);                      //print errors
      //d.foo(c, d, df);                  //print errors
      d.foo(df);                          //print B:foo(double)
      d.foo(i);                           //print B:foo(float)
      //d.foo( );                         //print errors
      //d.foo(i, d, df);                  //print errors
      d.foo(c, b, f);                     //print D:foo(int, B, float)
      d.foo(f);                           //print D:foo(float)
      d.foo(c);                           //print D:foo(float)
      d.foo(s, d, df);                    //print B:foo(short, B, double)
      //d.foo(i, d);                      //print errors

      System.out.println("b.caller");     //print b.caller
      b.caller( );

   }
}
