using System;   
using System.Threading;   
    
  public   class   MonitorSample   
  {   
  public   static   void   Main(String[]   args)   
  {   
  int   result   =   0;     
  Cell   cell   =   new   Cell(   );   
    
  CellProd   prod   =   new   CellProd(cell,   20);     
    
  Thread   producer   =   new   Thread(new   ThreadStart(prod.ThreadRun));   
    
  try   
  {   
  producer.Start();   
    
  producer.Join(   );   
  Console.ReadLine();   
  }   
  catch   (ThreadStateException   e)   
  {   
  Console.WriteLine(e);       
  result   =   1;     
  }   
  catch   (ThreadInterruptedException   e)   
  {   
  Console.WriteLine(e);     
  result   =   1;   
  }   
  Environment.ExitCode   =   result;   
  }   
  }   
    
  public   class   CellProd   
  {   
  Cell   cell;                     
  int   quantity   =   1;     
    
  public   CellProd(Cell   box,   int   request)   
  {   
  cell   =   box;                       
  quantity   =   request;       
  }   
  public   void   ThreadRun(   )   
  {   
  for(int   looper=1;   looper<=quantity;   looper++)   
  {   
  cell.WriteToCell(looper);   
  }   
  }   
  }   
    
    
  public   class   Cell   
  {   
  int   cellContents;                   
  bool   readerFlag   =   false;     
          
  public   void   WriteToCell(int   n)   
  {   
  lock(this)     
  {   
  if   (readerFlag)   
  {       
  try   
  {   
  Monitor.Wait(this);     
  }   
  catch   (SynchronizationLockException   e)   
  {   
  Console.WriteLine(e);   
  }   
  catch   (ThreadInterruptedException   e)   
  {   
  Console.WriteLine(e);   
  }   
  }   
  cellContents   =   n;   
Console.WriteLine("Produce:   {0}",cellContents);   
  Thread.Sleep(1000);//放在这里   
  Monitor.Pulse(this);     
  }     
  }   
  } 