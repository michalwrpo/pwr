with Ada.Text_IO; use Ada.Text_IO;
with Ada.Numerics.Float_Random; use Ada.Numerics.Float_Random;
with Random_Seeds; use Random_Seeds;
with Ada.Real_Time; use Ada.Real_Time;
with RW_Monitor; use RW_Monitor;

procedure  Mutex_Template is


-- Processes 
  Nr_Of_Readers : constant Integer := 10;
  Nr_Of_Writers : constant Integer := 5;
  Nr_Of_Processes : constant Integer := Nr_Of_Readers + Nr_Of_Writers;

  Min_Steps : constant Integer := 50 ;
  Max_Steps : constant Integer := 100 ;

  Min_Delay : constant Duration := 0.01;
  Max_Delay : constant Duration := 0.05;

-- States of a Process 

  type Process_State is (
    Local_Section,
    Start,
    Reading_Room,
    Stop
    );

-- 2D Board display board

  Board_Width  : constant Integer := Nr_Of_Processes;
  Board_Height : constant Integer := Process_State'Pos( Process_State'Last ) + 1;

-- Timing

  Start_Time : Time := Clock;  -- global startnig time

-- Random seeds for the tasks' random number generators
 
  Seeds : Seed_Array_Type( 1..Nr_Of_Processes ) := Make_Seeds( Nr_Of_Processes );

-- Types, procedures and functions

  -- Postitions on the board
  type Position_Type is record	
    X: Integer range 0 .. Board_Width - 1; 
    Y: Integer range 0 .. Board_Height - 1; 
  end record;	   

  -- traces of Processes
  type Trace_Type is record 	      
    Time_Stamp:  Duration;	      
    Id : Integer;
    Position: Position_Type;      
    Symbol: Character;	      
  end record;	      

  type Trace_Array_type is  array(0 .. Max_Steps) of Trace_Type;

  type Traces_Sequence_Type is record
    Last: Integer := -1;
    Trace_Array: Trace_Array_type ;
  end record; 


  procedure Print_Trace( Trace : Trace_Type ) is
    Symbol : String := ( ' ', Trace.Symbol );
  begin
    Put_Line(
        Duration'Image( Trace.Time_Stamp ) & " " &
        Integer'Image( Trace.Id ) & " " &
        Integer'Image( Trace.Position.X ) & " " &
        Integer'Image( Trace.Position.Y ) & " " &
        ( ' ', Trace.Symbol ) -- print as string to avoid: '
      );
  end Print_Trace;

  procedure Print_Traces( Traces : Traces_Sequence_Type ) is
  begin
    for I in 0 .. Traces.Last loop
      Print_Trace( Traces.Trace_Array( I ) );
    end loop;
  end Print_Traces;


  -- task Printer collects and prints reports of traces and the line with the parameters

  task Printer is
    entry Report( Traces : Traces_Sequence_Type );
  end Printer;
  
  task body Printer is 
  begin
  
    -- Collect and print the traces
    
    for I in 1 .. Nr_Of_Processes loop -- range for TESTS !!!
        accept Report( Traces : Traces_Sequence_Type ) do
          -- Put_Line("I = " & I'Image );
          Print_Traces( Traces );
        end Report;
      end loop;

    -- Prit the line with the parameters needed for display script:

    Put(
      "-1 "&
      Integer'Image( Nr_Of_Processes ) &" "&
      Integer'Image( Board_Width ) &" "&
      Integer'Image( Board_Height ) &" "       
    );
    for I in Process_State'Range loop
      Put( I'Image &";" );
    end loop;
    Put_Line("EXTRA_LABEL;"); -- Place labels with extra info here (e.g. "MAX_TICKET=...;" for Backery). 

  end Printer;


  -- Processes
  type Process_Type is record
    Id: Integer;
    Symbol: Character;
    Position: Position_Type;    
  end record;


  task type Reader_Task_Type is	
    entry Init(Id: Integer; Seed: Integer);
    entry Start;
  end Reader_Task_Type;	

  task body Reader_Task_Type is
    G : Generator;
    Process : Process_Type;
    Time_Stamp : Duration;
    Nr_of_Steps: Integer;
    Traces: Traces_Sequence_Type; 

    procedure Store_Trace is
    begin  
      Traces.Last := Traces.Last + 1;
      Traces.Trace_Array( Traces.Last ) := ( 
          Time_Stamp => Time_Stamp,
          Id => Process.Id,
          Position => Process.Position,
          Symbol => Process.Symbol
        );
    end Store_Trace;

    procedure Change_State( State: Process_State ) is
    begin
      Time_Stamp := To_Duration ( Clock - Start_Time ); -- reads global clock
      Process.Position.Y := Process_State'Pos( State );
      Store_Trace;
    end;
    

  begin
    accept Init(Id: Integer; Seed: Integer) do
      Reset(G, Seed); 
      Process.Id := Id;
      Process.Symbol := 'R';
      -- Initial position 
      Process.Position := (
          X => Id,
          Y => Process_State'Pos( LOCAL_SECTION )
        );
      -- Number of steps to be made by the Process  
      Nr_of_Steps := Min_Steps + Integer( Float(Max_Steps - Min_Steps) * Random(G));
      -- Time_Stamp of initialization
      Time_Stamp := To_Duration ( Clock - Start_Time ); -- reads global clock
      Store_Trace; -- store starting position
    end Init;
    
    -- wait for initialisations of the remaining tasks:
    accept Start do
      null;
    end Start;

--    for Step in 0 .. Nr_of_Steps loop
    for Step in 0 .. Nr_of_Steps/4 - 1  loop  -- TEST !!!
      -- LOCAL_SECTION - start
      delay Min_Delay+(Max_Delay-Min_Delay)*Duration(Random(G));
      -- LOCAL_SECTION - end

      Change_State( START ); -- starting ENTRY_PROTOCOL
      -- implement the ENTRY_PROTOCOL here ...
      Start_Read;

      Change_State( READING_ROOM ); -- starting CRITICAL_SECTION

      -- CRITICAL_SECTION - start
      delay Min_Delay+(Max_Delay-Min_Delay)*Duration(Random(G));
      -- CRITICAL_SECTION - end

      Change_State( STOP ); -- starting EXIT_PROTOCOL
      -- implement the EXIT_PROTOCOL here ...
      Stop_Read;

      Change_State( LOCAL_SECTION ); -- starting LOCAL_SECTION      
    end loop;
    
    Printer.Report( Traces );
  end Reader_Task_Type;

  task type Writer_Task_Type is	
    entry Init(Id: Integer; Seed: Integer);
    entry Start;
  end Writer_Task_Type;	

  task body Writer_Task_Type is
    G : Generator;
    Process : Process_Type;
    Time_Stamp : Duration;
    Nr_of_Steps: Integer;
    Traces: Traces_Sequence_Type; 

    procedure Store_Trace is
    begin  
      Traces.Last := Traces.Last + 1;
      Traces.Trace_Array( Traces.Last ) := ( 
          Time_Stamp => Time_Stamp,
          Id => Process.Id,
          Position => Process.Position,
          Symbol => Process.Symbol
        );
    end Store_Trace;

    procedure Change_State( State: Process_State ) is
    begin
      Time_Stamp := To_Duration ( Clock - Start_Time ); -- reads global clock
      Process.Position.Y := Process_State'Pos( State );
      Store_Trace;
    end;
    

  begin
    accept Init(Id: Integer; Seed: Integer) do
      Reset(G, Seed); 
      Process.Id := Id;
      Process.Symbol := 'W';
      -- Initial position 
      Process.Position := (
          X => Id,
          Y => Process_State'Pos( LOCAL_SECTION )
        );
      -- Number of steps to be made by the Process  
      Nr_of_Steps := Min_Steps + Integer( Float(Max_Steps - Min_Steps) * Random(G));
      -- Time_Stamp of initialization
      Time_Stamp := To_Duration ( Clock - Start_Time ); -- reads global clock
      Store_Trace; -- store starting position
    end Init;
    
    -- wait for initialisations of the remaining tasks:
    accept Start do
      null;
    end Start;

--    for Step in 0 .. Nr_of_Steps loop
    for Step in 0 .. Nr_of_Steps/4 - 1  loop  -- TEST !!!
      -- LOCAL_SECTION - start
      delay Min_Delay+(Max_Delay-Min_Delay)*Duration(Random(G));
      -- LOCAL_SECTION - end

      Change_State( START ); -- starting ENTRY_PROTOCOL
      -- implement the ENTRY_PROTOCOL here ...
      Start_Write;

      Change_State( READING_ROOM ); -- starting CRITICAL_SECTION

      -- CRITICAL_SECTION - start
      delay Min_Delay+(Max_Delay-Min_Delay)*Duration(Random(G));
      -- CRITICAL_SECTION - end

      Change_State( STOP ); -- starting EXIT_PROTOCOL
      -- implement the EXIT_PROTOCOL here ...
      Stop_Write;
      
      Change_State( LOCAL_SECTION ); -- starting LOCAL_SECTION      
    end loop;
    
    Printer.Report( Traces );
  end Writer_Task_Type;

-- local for main task

  Reader_Tasks: array (0 .. Nr_Of_Readers-1) of Reader_Task_Type;
  Writer_Tasks: array (0 .. Nr_Of_Writers-1) of Writer_Task_Type; 

begin 
  -- init tarvelers tasks
  for I in Reader_Tasks'Range loop
    Reader_Tasks(I).Init(I, Seeds(I+1));   -- `Seeds(I+1)` is ugly :-(
  end loop;

  for I in Writer_Tasks'Range loop
    Writer_Tasks(I).Init(I + Nr_Of_Readers, Seeds(I+ 1 + Nr_Of_Readers));   -- `Seeds(I+1)` is ugly :-(
  end loop;

  -- start tarvelers tasks
  for I in Reader_Tasks'Range loop
    Reader_Tasks(I).Start;
  end loop;

  for I in Writer_Tasks'Range loop
    Writer_Tasks(I).Start;
  end loop;

end Mutex_Template;

