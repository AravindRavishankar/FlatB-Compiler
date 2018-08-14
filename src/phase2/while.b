declblock{
	int a[102],i,j,x;
}

codeblock{
   i=1;
   
   while i <100
   {
     a[i]= 100 -i ;
	i=i+1; 
  }
   i=0;
   while i < 99
   {
     j=0;
     while j< 99
     {
       if a[j] > a[j+1]
       {
          x= a[j];
          a[j]= a[j+1];
          a[j+1]=x;
       }
        j=j+1;
     }
     i=i+1;
   }

}

