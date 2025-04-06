with Ada.Text_IO; use Ada.Text_IO;
with Ada.Numerics.Float_Random; use Ada.Numerics.Float_Random;
with Random_Seeds; use Random_Seeds;
with Ada.Real_Time; use Ada.Real_Time;
with Ada.Characters.Handling; use Ada.Characters.Handling;

procedure  Travelers is


-- Travelers moving on the board

  Nr_Of_Travelers : constant Integer := 15;

  Min_Steps : constant Integer := 10 ;
  Max_Steps : constant Integer := 100 ;

  Min_Delay : constant Duration := 0.01;
  Max_Delay : constant Duration := 0.05;

-- 2D Board with torus topology

  Board_Width  : constant Integer := 15;
  Board_Height : constant Integer := 15;

-- Timing

  Start_Time : Time := Clock;  -- global starting time

-- Random seeds for the tasks' random number generators
 
  Seeds : Seed_Array_Type(1..Nr_Of_Travelers) := Make_Seeds(Nr_Of_Travelers);

-- Types, procedures and functions

  type posx is mod Board_Width;
  type posy is mod Board_Height;

  -- Postitions on the board
  type Position_Type is record	
    X: posx; 
    Y: posy; 
  end record;

  protected type Field_Type is
    entry Take;
    procedure Free; 
  private
    Is_Free : Boolean := True; 
  end Field_Type;

  protected body Field_Type is
    entry Take when Is_Free is
    begin
        Is_Free := False;
    end Take;

    procedure Free is
    begin
        Is_Free := True;
    end Free;
  end Field_Type;

  type Field_Access is access all Field_Type;
  type Board_Type is array (posx'Range, posy'Range) of Field_Access;
  
  Board : Board_Type;

  -- elementary steps
  procedure Move_Down(Position: in out Position_Type; Success: out Boolean) is
    New_Y : posy := Position.Y + 1;
  begin
    select
      Board(Position.X, New_Y).Take;
      Board(Position.X, Position.Y).Free;
      Position.Y := New_Y;
      Success := True;
    or
      delay 3.0 * Max_Delay;
      Success := False;
    end select;
  end Move_Down;

  procedure Move_Up(Position: in out Position_Type; Success: out Boolean) is
    New_Y : posy := Position.Y - 1;
  begin
    select
      Board(Position.X, New_Y).Take;
      Position.Y := New_Y;
      Board(Position.X, Position.Y + 1).Free;
      Success := True;
    or
      delay 3.0 * Max_Delay;
      Success := False;
    end select;
  end Move_Up;

  procedure Move_Right(Position: in out Position_Type; Success: out Boolean) is
    New_X : posx := Position.X + 1;
  begin
    select
      Board(New_X, Position.Y).Take;
      Board(Position.X, Position.Y).Free;
      Position.X := New_X;
      Success := True;
    or
      delay 3.0 * Max_Delay;
      Success := False;
    end select;
  end Move_Right;

  procedure Move_Left(Position: in out Position_Type; Success: out Boolean) is
    New_X : posx := Position.X - 1;
  begin
    select
      Board(New_X, Position.Y).Take;
      Board(Position.X, Position.Y).Free;
      Position.X := New_X;
      Success := True;
    or
      delay 3.0 * Max_Delay;
      Success := False;
    end select;
  end Move_Left;

  -- traces of travelers
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
        posx'Image( Trace.Position.X ) & " " &
        posy'Image( Trace.Position.Y ) & " " &
        ( ' ', Trace.Symbol ) -- print as string to avoid: '
      );
  end Print_Trace;

  procedure Print_Traces( Traces : Traces_Sequence_Type ) is
  begin
    for I in 0 .. Traces.Last loop
      Print_Trace( Traces.Trace_Array( I ) );
    end loop;
  end Print_Traces;

  -- task Printer collects and prints reports of traces
  task Printer is
    entry Report( Traces : Traces_Sequence_Type );
  end Printer;
  
  task body Printer is 
  begin
    for I in 1 .. Nr_Of_Travelers loop -- range for TESTS !!!
        accept Report( Traces : Traces_Sequence_Type ) do
          Print_Traces( Traces );
        end Report;
      end loop;
  end Printer;


  -- travelers
  type Traveler_Type is record
    Id: Integer;
    Symbol: Character;
    Position: Position_Type;    
  end record;


  task type Traveler_Task_Type is	
    entry Init(Id: Integer; Seed: Integer; Symbol: Character);
    entry Start;
  end Traveler_Task_Type;	

  task body Traveler_Task_Type is
    G : Generator;
    Traveler : Traveler_Type;
    Time_Stamp : Duration;
    Nr_of_Steps: Integer;
    Traces: Traces_Sequence_Type; 
    Deadlock: Boolean := False;

    procedure Store_Trace is
    begin  
      Traces.Last := Traces.Last + 1;
      Traces.Trace_Array( Traces.Last ) := ( 
          Time_Stamp => Time_Stamp,
          Id => Traveler.Id,
          Position => Traveler.Position,
          Symbol => Traveler.Symbol
        );
    end Store_Trace;
    
    procedure Make_Step is
      N : Integer;
      Success : Boolean := False;
    begin
      N := Integer( Float'Floor(4.0 * Random(G)) );
      case N is
        when 0 =>
          Move_Up(Traveler.Position, Success);
        when 1 =>
          Move_Down(Traveler.Position, Success);
        when 2 =>
          Move_Left(Traveler.Position, Success);
        when 3 =>
          Move_Right(Traveler.Position, Success);
        when others =>
          Put_Line("Invalid move value: " & Integer'Image(N));
      end case;

      if not Success then
        Traveler.Symbol := To_Lower(Traveler.Symbol);
        Deadlock := True;
      end if;
    end Make_Step;

  begin
    accept Init(Id: Integer; Seed: Integer; Symbol: Character) do
      Reset(G, Seed); 
      Traveler.Id := Id;
      Traveler.Symbol := Symbol;

      declare
      Try_Limit : constant Integer := 1000;
      Try_Count : Integer := 0;
      Init_X : posx;
      Init_Y : posy;

      -- Random initial position:
      begin
        loop
          -- Random position candidate
          Init_X := posx(Float'Floor(Float(Board_Width) * Random(G)));
          Init_Y := posy(Float'Floor(Float(Board_Height) * Random(G)));

          -- Try to take the field
          declare
            Success : Boolean := False;
          begin
            select
              Board(Init_X, Init_Y).Take;
              Success := True;
            or
              delay 0.001;  -- quick retry delay
            end select;

            if Success then
              Traveler.Position := (X => Init_X, Y => Init_Y);
              exit;
            else
              Try_Count := Try_Count + 1;
              exit when Try_Count >= Try_Limit;
            end if;
          end;
        end loop;

        if Try_Count >= Try_Limit then
          Deadlock := True;
        else
          Store_Trace;  -- only store if acquired a position
        end if;

        -- Number of steps to be made by the traveler  
        Nr_of_Steps := Min_Steps + Integer(Float(Max_Steps - Min_Steps) * Random(G));
        -- Time_Stamp of initialization
        Time_Stamp := To_Duration(Clock - Start_Time); -- reads global clock
      end;
      Store_Trace; -- store starting position
      -- Number of steps to be made by the traveler  
      Nr_of_Steps := Min_Steps + Integer( Float(Max_Steps - Min_Steps) * Random(G));
      -- Time_Stamp of initialization
      Time_Stamp := To_Duration ( Clock - Start_Time ); -- reads global clock
    end Init;
    
    -- wait for initialisations of the remaining tasks:
    accept Start do
      null;
    end Start;

    for Step in 0 .. Nr_of_Steps loop
      exit when Deadlock;
      delay Min_Delay+(Max_Delay-Min_Delay)*Duration(Random(G));
      -- do action ...
      Make_Step;
      Store_Trace;
      Time_Stamp := To_Duration ( Clock - Start_Time ); -- reads global clock
    end loop;
    Printer.Report( Traces );
  end Traveler_Task_Type;


-- local for main task

  Travel_Tasks: array (0 .. Nr_Of_Travelers-1) of Traveler_Task_Type; -- for tests
  Symbol : Character := 'A';
begin 
  
  -- Print the line with the parameters needed for display script:
  Put_Line(
      "-1 " & Integer'Image( Nr_Of_Travelers ) 
      & " " & Integer'Image( Board_Width ) 
      & " " & Integer'Image( Board_Height )      
    );

  -- init Board
  for X in posx'Range loop
    for Y in posy'Range loop
      Board(X, Y) := new Field_Type;
    end loop;
  end loop;



  -- init tarvelers tasks
  for I in Travel_Tasks'Range loop
    Travel_Tasks(I).Init( I, Seeds(I+1), Symbol );   -- `Seeds(I+1)` is ugly :-(
    Symbol := Character'Succ( Symbol );
  end loop;

  -- start tarvelers tasks
  for I in Travel_Tasks'Range loop
    Travel_Tasks(I).Start;
  end loop;

end Travelers;

