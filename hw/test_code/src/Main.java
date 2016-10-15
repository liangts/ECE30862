class Main {
    public static void main(String args[]) {
        B b = new B( );
        D1 d1 = new D1( );
        D2 d2 = new D2( );
        b.m1( ); // Q13
        d1.m1( ); // Q14
        b.m2( ); // Q15
        d1.m2( ); // Q16
        d2.m2( ); // Q17
        b.m4( ); // Q18
        d1.m4( ); // Q19
        d2.m4( ); // Q20
        b.m5( ); // Q21
        d2.m5( ); // Q22
        b = d1;
        b.m1( ); // Q23
        b.m2( ); // Q24
        b = d2;
        b.m2( ); // Q25
        b.m4( ); // Q26
        b.m5( ); // Q27
        d2 = b; // Q28
        d2 = (D2) b; // Q29
        d1 = (D1) b; //Q30
    }
}