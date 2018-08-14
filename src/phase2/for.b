declblock{
	int a;
	int x[100];
}

codeblock{
  for a = 1, 10, 3 {
    println "First for";
	x[a]=3;
  }
  for a = 1, 10 {
    println "Second for";
  }
  x[1]=3;
}

