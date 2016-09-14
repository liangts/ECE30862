import java.io.*;

class Main {

   public static void main(String args[]) {
      C0 c01 = new C0( );
      C0 c02 = new C0(1,2);
      C1 c11 = new C1( );
      C1 c12 = new C1(3, 4, 5.0f);

      System.out.println("c01.a.intValue( ): " + c01.a.intValue( )); // c01.a.intValue( ): 0
      System.out.println("c01.b.intValue( ): " + c01.b.intValue( )); // c01.b.intValue( ): 0
      System.out.println("c01.x: " + c01.x); // c01.x: 0
      System.out.println("c01.y: " + c01.y); // c01.y: 0

      System.out.println("c02.a.intValue( ): " + c02.a.intValue( )); // c02.a.intValue( ): 1
      System.out.println("c02.b.intValue( ): " + c02.b.intValue( )); // c02.b.intValue( ): 2
      System.out.println("c02.x: " + c02.x); // c02.x: 1
      System.out.println("c02.y: " + c02.y); // c02.y: 2

      System.out.println("c11.a.intValue( ): " + c11.a.intValue( )); // c11.a.intValue( ): 0
      System.out.println("c11.b.intValue( ): " + c11.b.intValue( )); // c11.b.intValue( ): 0
      System.out.println("c11.c.floatValue( ): " + c11.c.floatValue( )); // c11.c.floatValue( ): 1.5
      System.out.println("c11.x: " + c11.x); // c11.x: 0
      System.out.println("c11.y: " + c11.y); // c11.y: 0
      System.out.println("c11.z: " + c11.z); // c11.z: 1.5

      c01 = c12;
      System.out.println("c12.a.intValue( ): " + c01.a.intValue( )); // c12.a.intValue( ): 3
      System.out.println("c12.b.intValue( ): " + c01.b.intValue( )); // c12.b.intValue( ): 4
      System.out.println("c12.c.floatValue( ): " + ((C1) c01).c.floatValue( )); // c12.c.floatValue( ): 5.0
      System.out.println("c12.x: " + c01.x); // c12.x: 0
      System.out.println("c12.y: " + c01.y); // c12.y: 0
      // System.out.println("c12.z: " + c01.z); // z is not defined in 
                                                // class C0, not visible
                                                // from a C0 reference.

      System.out.println("c02.getA( ): " + c02.getA( )); // c02.getA( ): -1
      System.out.println("c02.getB( ): " + c02.getB( )); // c02.getB( ): -2
      System.out.println("c02.getX( ): " + c02.getX( )); // c02.getX( ): -1
      System.out.println("c02.getY( ): " + c02.getY( )); // c02.getY( ): -2

      System.out.println("c12.getA( ): " + c01.getA( )); // c12.getA( ): -3
      System.out.println("c12.getB( ): " + c01.getB( )); // c12.getB( ): -4
      System.out.println("c12.getC( ): " + ((C1) c01).getC( )); // c12.getC( ): 5.0
      System.out.println("c12.getX( ): " + c01.getX( )); // c12.getX( ): 0
      System.out.println("c01.getY( ): " + c01.getY( )); // c01.getY( ): 1
      System.out.println("c01.getZ( ): " + c01.getY( )); // c01.getZ( ): 1
   }
}
