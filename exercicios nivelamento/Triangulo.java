class Triangulo
{
	public static void main(String args[])
	{
		int a, b ,c;
		a= MyIO.readInt();
		b= MyIO.readInt();
		c= MyIO.readInt();
		 if (a == b && a == c)
		 {
			 MyIO.println("Equilatero");
		 }
		 else if ( a == b && a != c)
		 {
			 MyIO.println("Isosceles");
		 }
		 else if ( b== c && b != a)
		 {
			 MyIO.println("Isosceles");
		 }
		 else
			 MyIO.println("Escaleno");
	}
}

