with Ada.Text_IO; use Ada.Text_IO;
with Ada.Numerics.Float_Random; use Ada.Numerics.Float_Random;
with Random_Seeds; use Random_Seeds;
with Ada.Real_Time; use Ada.Real_Time;
with Ada.Characters.Handling; use Ada.Characters.Handling;
with System;

procedure  Travelers is
   -- Travelers moving on the board
   Nr_Of_Travelers : constant Integer := 15;
   Max_Occupants : constant Integer := 25;
   Max_Traps : constant Integer := 100;

   Min_Steps : constant Integer := 10 ;
   Max_Steps : constant Integer := 100 ;

   Min_Delay : constant Duration := 0.01;
   Max_Delay : constant Duration := 0.05;

   -- 2D Board with torus topology

   Board_Width  : constant Integer := 15;
   Board_Height : constant Integer := 15;

   -- Timing

   Start_Time : Time := Clock;  -- global starting time
   Occupant_Spawn_End: Time := Start_Time + Seconds (2);
   Occupant_Time_Limit : Time := Start_Time + Seconds (3);

   -- Random seeds for the tasks' random number generators

   Seeds : Seed_Array_Type(1 .. Board_Height * Board_Width) := Make_Seeds(Board_Height * Board_Width);


   -- Types, procedures and functions

   type posx is mod Board_Width;
   type posy is mod Board_Height;

   -- Postitions on the board
   type Position_Type is record	
      X: posx; 
      Y: posy; 
   end record;

   protected type Field_Protection_Type is
      entry Take(Traveler: Boolean);
      procedure Free; 
      function OccupantPresent return Boolean;
      procedure Trap;
      function IsTrapped return Boolean;
   private
      Is_Free : Boolean := True; 
      By_Traveler : Boolean := True;
      Trapped : Boolean := False;
   end Field_Protection_Type;

   protected body Field_Protection_Type is
      entry Take(Traveler: Boolean) when Is_Free is
      begin
         Is_Free := False;
         By_Traveler := Traveler;
      end Take;

      procedure Free is
      begin
         Is_Free := True;
         By_Traveler := True;
      end Free;

      function OccupantPresent return Boolean is 
      begin
         return not By_Traveler;
      end OccupantPresent;

      procedure Trap is
      begin
         Trapped := True;
      end Trap;

      function IsTrapped return Boolean is
      begin
         return Trapped;
      end IsTrapped;
   end Field_Protection_Type;

   type Field_Access is access all Field_Protection_Type;
   type Board_Type is array (posx'Range, posy'Range) of Field_Access;

   Board : Board_Type;

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
      if Trace.Symbol = '*' then
         Symbol := "\*";
      end if;
      Put_Line(
         Duration'Image( Trace.Time_Stamp ) & " " &
         Integer'Image( Trace.Id ) & " " &
         posx'Image( Trace.Position.X ) & " " &
         posy'Image( Trace.Position.Y ) & " " &
         Symbol
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
      loop
         select
            accept Report( Traces : Traces_Sequence_Type ) do
               Print_Traces( Traces );
            end Report;
         or
            delay until Occupant_Time_Limit;
            exit;
         end select;
      end loop;
   end Printer;

   -- occupants

   protected Occupant_ID is
      entry Get(OID: out Integer);
   private
      ID : Integer := Nr_Of_Travelers;
      Free : Boolean := True;
   end Occupant_ID;

   protected body Occupant_ID is
      entry Get(OID: out Integer)
         when Free is
      begin
         Free := False;
         if ID < Nr_Of_Travelers + Max_Occupants then
            OID := ID;
            ID := ID + 1;
         else
            OID := -1;
         end if;
         Free := True;
      end Get;
   end Occupant_ID;

   protected Trap_ID is
      entry Get(TID: out Integer);
   private
      ID : Integer := Nr_Of_Travelers + Max_Occupants;
      Free : Boolean := True;
   end Trap_ID;

   protected body Trap_ID is
      entry Get(TID: out Integer)
         when Free is
      begin
         Free := False;
         if ID < Nr_Of_Travelers + Max_Occupants + Max_Traps then
            TID := ID;
            ID := ID + 1;
         else
            TID := -1;
         end if;
         Free := True;
      end Get;
   end Trap_ID;

   type Occupant_Type is record
      Id: Integer;
      Symbol: Character;
      Position: Position_Type;
      Lifespan: Integer;
   end record;

   task type Occupant_Task_Type is
      entry Init(Id: Integer; Symbol: Character; Position: Position_Type; Lifespan: Integer);
      entry Move(X: out posx; Y: out posy);
   end Occupant_Task_Type;

   task body Occupant_Task_Type is
      G : Generator;
      Occupant : Occupant_Type;
      Time_Stamp : Duration;
      Failed : Boolean := False;
      Traces : Traces_Sequence_Type; 
      Timer : Time;
      Success : Boolean;

      procedure Store_Trace is
      begin  
         Traces.Last := Traces.Last + 1;
         Traces.Trace_Array( Traces.Last ) := ( 
            Time_Stamp => Time_Stamp,
            Id => Occupant.Id,
            Position => Occupant.Position,
            Symbol => Occupant.Symbol
         );
      end Store_Trace;

   begin
      select
         accept Init(Id : Integer; Symbol : Character; Position: Position_Type; Lifespan: Integer) do
            Occupant.Id := Id;
            Occupant.Symbol := Symbol;
            Occupant.Position := Position;
            Occupant.Lifespan := Lifespan;
            Timer := Clock + Milliseconds (Occupant.Lifespan);

            Time_Stamp := To_Duration(Clock - Start_Time);
            Store_Trace;
         end Init;

         loop
            if Clock > Timer then
               exit;
            end if;

            select
               accept Move(X: out posx; Y: out posy) do
                  Success := False;
                  select
                     Board(Occupant.Position.X, Occupant.Position.Y - 1).Take(False);
                     Occupant.Position.Y := Occupant.Position.Y - 1;
                     Time_Stamp := To_Duration ( Clock - Start_Time ); 
                     Board(Occupant.Position.X, Occupant.Position.Y + 1).Free;
                     Success := True;
                  or
                     delay 0.005;
                     Success := False;
                  end select;

                  if not Success then
                     select
                        Board(Occupant.Position.X, Occupant.Position.Y + 1).Take(False);
                        Occupant.Position.Y := Occupant.Position.Y + 1;
                        Time_Stamp := To_Duration ( Clock - Start_Time ); 
                        Board(Occupant.Position.X, Occupant.Position.Y - 1).Free;
                        Success := True;
                     or
                        delay 0.005;
                        Success := False;
                     end select;
                  end if;

                  if not Success then
                     select
                        Board(Occupant.Position.X - 1, Occupant.Position.Y).Take(False);
                        Occupant.Position.X := Occupant.Position.X - 1;
                        Time_Stamp := To_Duration ( Clock - Start_Time );
                        Board(Occupant.Position.X + 1, Occupant.Position.Y).Free;
                        Success := True;
                     or
                        delay 0.005;
                        Success := False;
                     end select;
                  end if;

                  if not Success then
                     select
                        Board(Occupant.Position.X + 1, Occupant.Position.Y).Take(False);
                        Occupant.Position.X := Occupant.Position.X + 1;
                        Time_Stamp := To_Duration ( Clock - Start_Time ); 
                        Board(Occupant.Position.X - 1, Occupant.Position.Y).Free;
                        Success := True;
                     or
                        delay 0.005;
                        Success := False;
                     end select;
                  end if;
                  
                  Store_Trace;
                  X := Occupant.Position.X;
                  Y := Occupant.Position.Y;
               end Move;

               if Board(Occupant.Position.X, Occupant.Position.Y).IsTrapped then
                  Occupant.Symbol := '*';
                  Timer := Clock;
                  Time_Stamp := To_Duration ( Clock - Start_Time ); -- reads global clock
                  Store_Trace;
                  delay 0.1;
                  Board(Occupant.Position.X, Occupant.Position.Y).Free;
                  Occupant.Symbol := '.';
                  Time_Stamp := To_Duration ( Clock - Start_Time ); -- reads global clock
                  Store_Trace;
               end if;
            or
               delay To_Duration (Milliseconds (40));
               Time_Stamp := To_Duration(Clock - Start_Time);
               Store_Trace;
            end select;
         end loop;   

         Board(Occupant.Position.X, Occupant.Position.Y).Free;
         Time_Stamp := To_Duration(Clock - Start_Time);
         Occupant.Symbol := '.';
         Store_Trace;
         if Occupant.Id - Nr_Of_Travelers < Max_Occupants then
            Printer.Report( Traces );
         end if;
      or
         delay until Occupant_Time_Limit;
      end select;

   end Occupant_Task_Type;

   task type Field_Task_Type is
      entry Init(Position: Position_Type; Seed: Integer);
      entry Occupy(Until_Time: Time);
      entry Move;
      entry Show;
   end Field_Task_Type;

   type Board_Interactive_Type is array (posx'Range, posy'Range) of Field_Task_Type;
   Board_Interactive : Board_Interactive_Type;

   task body Field_Task_Type is
      Trapped: Boolean := False;
      Occupant: Occupant_Task_Type;
      G: Generator;
      Pos: Position_Type;
      Rand: Integer;
      OID: Integer;
      TID: Integer;
      Occupied: Boolean := False;
      Lifespan: Integer;
      Time_Limit: Time;
      New_X: posx;
      New_Y: posy;
      Traces : Traces_Sequence_Type; 
      Time_Stamp : Duration;

      procedure Store_Trace is
      begin  
         Traces.Last := Traces.Last + 1;
         Traces.Trace_Array( Traces.Last ) := ( 
            Time_Stamp => Time_Stamp,
            Id => TID,
            Position => Pos,
            Symbol => '#'
         );
      end Store_Trace;
      
   begin
      accept Init(Position: Position_Type; Seed: Integer) do
         Pos := Position;
         Reset(G, Seed);
         Rand := Integer( Float'Floor( 10.0 * Random(G) ) );
         if Rand = 0 then
            Trap_ID.Get(TID);
            if TID > 0 then
               Trapped := True;
               Time_Stamp := To_Duration(Clock - Start_Time);
               Store_Trace;
               Board(Pos.X, Pos.Y).Trap;
            end if;
         end if;
      end Init;

      loop
         if not Trapped then
            if Clock > Occupant_Spawn_End then
               exit;
            end if;

            Rand := Integer( Float'Floor( 20.0 * Random(G) ) );

            select
               accept Occupy(Until_Time: Time) do
                  Occupied := True;
                  Time_Limit := Until_Time;
               end Occupy;
            or
               delay To_Duration ( Milliseconds( Rand * 10 ) );
            end select;

            if Rand = 0 then
               select
                  Board(Pos.X, Pos.Y).Take(False);
                  Occupant_ID.Get(OID);
                  if OID > 0 then
                     Lifespan := Integer(Float'Floor(Random(G) * 900.0 + 100.0));
                     Occupant.Init(OID, Integer'Image(OID mod 10)(2), Pos, Lifespan);
                     Occupied := True;
                     Time_Limit := Clock + Milliseconds (Lifespan);
                  else
                     Board(Pos.X, Pos.Y).Free;
                  end if;
               or
                  delay 0.001;
               end select;
            end if;

            if Occupied then
               select
                  accept Move do
                     Occupant.Move(New_X, New_Y);
                     if not (New_X = Pos.X and New_Y = Pos.Y) then
                        Board_Interactive(New_X, New_Y).Occupy(Time_Limit);
                        Occupied := False;
                     end if; 
                  end Move;   
               or
                  delay until Time_Limit;
                  Occupied := False;
               end select;
            end if;
         else
            select
               accept Occupy(Until_Time: Time) do
                  Occupied := True;
                  delay 0.12;
                  Time_Stamp := To_Duration(Clock - Start_Time);
                  Store_Trace;
                  Occupied := False;
               end Occupy;
            or
               accept Show do
                  Time_Stamp := To_Duration(Clock - Start_Time);
                  Store_Trace;
               end Show;
            or
               delay until Occupant_Time_Limit;
               exit;
            end select;
         end if;
      end loop;

      if Trapped then
         Printer.Report (Traces);
      end if;      
   end Field_Task_Type;

   -- elementary steps
   procedure Move_Down(Position: in out Position_Type; Success: out Boolean; Occupant: out Boolean; Time_Stamp: out Duration) is
      New_Y : posy := Position.Y + 1;
   begin
      if Board(Position.X, New_Y).OccupantPresent then
         Occupant := True;
         Board_Interactive(Position.X, New_Y).Move;
      else
         Occupant := False;
      end if;
      select
         Board(Position.X, New_Y).Take(True);
         Position.Y := New_Y;
         Time_Stamp := To_Duration ( Clock - Start_Time ); -- reads global clock
         Board(Position.X, Position.Y - 1).Free;
         Success := True;
      or
         delay 3.0 * Max_Delay;
         Success := False;
      end select;
   end Move_Down;

   procedure Move_Up(Position: in out Position_Type; Success: out Boolean; Occupant: out Boolean; Time_Stamp: out Duration) is
      New_Y : posy := Position.Y - 1;
   begin
      if Board(Position.X, New_Y).OccupantPresent then
         Occupant := True;
         Board_Interactive(Position.X, New_Y).Move;
      else
         Occupant := False;
      end if;
      select
         Board(Position.X, New_Y).Take(True);
         Position.Y := New_Y;
         Time_Stamp := To_Duration ( Clock - Start_Time ); -- reads global clock
         Board(Position.X, Position.Y + 1).Free;
         Success := True;
      or
         delay 3.0 * Max_Delay;
         Success := False;
      end select;
   end Move_Up;

   procedure Move_Right(Position: in out Position_Type; Success: out Boolean; Occupant: out Boolean; Time_Stamp: out Duration) is
      New_X : posx := Position.X + 1;
   begin
      if Board(New_X, Position.Y).OccupantPresent then
         Occupant := True;
         Board_Interactive(New_X, Position.Y).Move;
         delay Max_Delay;
      else
         Occupant := False;
      end if;
      select
         Board(New_X, Position.Y).Take(True);
         Position.X := New_X;
         Time_Stamp := To_Duration ( Clock - Start_Time ); -- reads global clock
         Board(Position.X - 1, Position.Y).Free;
         Success := True;
      or
         delay 3.0 * Max_Delay;
         Success := False;
      end select;
   end Move_Right;

   procedure Move_Left(Position: in out Position_Type; Success: out Boolean; Occupant: out Boolean; Time_Stamp: out Duration) is
      New_X : posx := Position.X - 1;
   begin
      if Board(New_X, Position.Y).OccupantPresent then
         Occupant := True;
         Board_Interactive(New_X, Position.Y).Move;
      else
         Occupant := False;
      end if;
      select
         Board(New_X, Position.Y).Take(True);
         Position.X := New_X;
         Time_Stamp := To_Duration ( Clock - Start_Time ); -- reads global clock
         Board(Position.X + 1, Position.Y).Free;
         Success := True;
      or
         delay 3.0 * Max_Delay;
         Success := False;
      end select;
   end Move_Left;

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
         Occupant : Boolean := False;
      begin
         N := Integer( Float'Floor(4.0 * Random(G)) );
         case N is
            when 0 =>
               Move_Up(Traveler.Position, Success, Occupant, Time_Stamp);
            when 1 =>
               Move_Down(Traveler.Position, Success, Occupant, Time_Stamp);
            when 2 =>
               Move_Left(Traveler.Position, Success, Occupant, Time_Stamp);
            when 3 =>
               Move_Right(Traveler.Position, Success, Occupant, Time_Stamp);
            when others =>
               Put_Line("Invalid move value: " & Integer'Image(N));
         end case;

         if not Success then
            if Occupant then
               Make_Step;
            else 
               Traveler.Symbol := To_Lower(Traveler.Symbol);
               Deadlock := True;
               Time_Stamp := To_Duration ( Clock - Start_Time ); -- reads global clock
            end if;
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
                  Board(Init_X, Init_Y).Take(True);
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
      end Init;
      
      -- wait for initialisations of the remaining tasks:
      accept Start do
         null;
      end Start;

      for Step in 0 .. Nr_of_Steps loop
         exit when Deadlock;
         delay Min_Delay + (Max_Delay - Min_Delay) * Duration(Random(G));
         -- do action ...
         Make_Step;
         Store_Trace;
         if Board(Traveler.Position.X, Traveler.Position.Y).IsTrapped then
               Traveler.Symbol := To_Lower(Traveler.Symbol);
               Deadlock := True;
               Time_Stamp := To_Duration ( Clock - Start_Time ); -- reads global clock
               Store_Trace;
               delay 0.1;
               Board(Traveler.Position.X, Traveler.Position.Y).Free;
               Traveler.Symbol := '.';
               Time_Stamp := To_Duration ( Clock - Start_Time ); -- reads global clock
               Store_Trace;
               Board_Interactive(Traveler.Position.X, Traveler.Position.Y).Show;
         end if;
      end loop;

      Printer.Report( Traces );
   end Traveler_Task_Type;


   -- local for main task

   Travel_Tasks : array (0 .. Nr_Of_Travelers-1) of Traveler_Task_Type; -- for tests
   Occupant_Tasks : array (0 .. Max_Occupants-1) of Occupant_Task_Type;
   --  O : Occupant_Task_Type;
   Symbol : Character := 'A';
begin
   -- Print the line with the parameters needed for display script:
   Put_Line(
      "-1 " & Integer'Image( Nr_Of_Travelers + Max_Occupants + Max_Traps ) 
      & " " & Integer'Image( Board_Width ) 
      & " " & Integer'Image( Board_Height )      
      );

   -- init Board
   for X in posx'Range loop
      for Y in posy'Range loop
         Board(X, Y) := new Field_Protection_Type;
      end loop;
   end loop;

   for X in posx'Range loop
      for Y in posy'Range loop
         Board_Interactive(X, Y).Init((X, Y), Seeds(Integer(Y) * Board_Width + Integer(X) + 1));
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
