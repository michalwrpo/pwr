# -----------------
# Simple escape the labyrinth game
# Michał Waluś 2024
# -----------------

clear

# starting position
pos_x=2
pos_y=1

# we round the numbers of columns and rows to the nearest
# odd number down, so that map ends with border
rows=$(( ( $(tput lines) - 1 ) / 2 * 2 + 1 ))
# everything is 2 characters wide, so number of columns is divided by two
cols=$(( ( $(tput cols) - 2 ) / 4 * 2 + 1 ))
total=$(( $rows * $cols ))

allowed=()

# row full of walls
for ((i = 0; i < cols; i++)); do
    allowed=(${allowed[*]} 0)
done

row1=${allowed[*]}

# row with alternating walls and empty spaces
for ((i = 0; i < cols; i++)); do
    if [[ $(( $i % 2 )) = 0 ]]; then
        allowed=(${allowed[*]} 0)
    else
        allowed=(${allowed[*]} 2)
    fi
done

row2=("${allowed[@]:$cols}")

# we fill out map with this pattern, so that 
# we can remove some walls and create the labyrinth
for ((i = 0; i < rows; i++)); do
    if [[ $(( $i % 2 )) = 0 ]]; then
        allowed=(${allowed[*]} ${row1[*]})
    else
        allowed=(${allowed[*]} ${row2[*]})
    fi
done

# We generate the maze with a modified version of Prim's algorithm.
# I don't know if it has a diffent name, I thought of it after seeing
# the aforementioned algorithm.
# We mark disconnected empty spaces as 2, connected as 1 and walls as 0.
# We start with marking starting position (1, 1) as connected and add 
# its neighbors to list of possible squares to connect next ('next'). 
# We add squares as pairs (2 entries to our list), first being a connected 
# square and second its disconnected neighbor. Then we randomly select 
# a pair from the list and if 2nd entry from pair isn't connected, we mark 
# it as connected, while also deleting the wall between them. Next we add
# all its disconnected neighbors to 'next' and repeat. The algorithm
# continues until there are no more possible connections to be made.

# starting pos
allowed[$(( $cols + 1 ))]=1

# its neighbors
next=($(( $cols + 1 )) $(( $cols + 3 )) $(( $cols + 1 )) $(( 3 * $cols + 1)) )

# check for disconnected neighbors
check() {
    s=$1
    
    snext=$(( $s - 2 ))
    if [[ ${allowed[$snext]} = 2 && $snext -gt 0 ]]; then
        next=(${next[@]} $s $snext)
    fi

    snext=$(( $s + 2 ))
    if [[ ${allowed[$snext]} = 2 && $snext -lt $total ]]; then
        next=(${next[@]} $s $snext)
    fi

    snext=$(( $s - 2 * $cols ))
    if [[ ${allowed[$snext]} = 2 && $snext -gt 0 ]]; then
        next=(${next[@]} $s $snext)
    fi

    snext=$(( $s + 2 * $cols ))
    if [[ ${allowed[$snext]} = 2 && $snext -lt $total ]]; then
        next=(${next[@]} $s $snext)

    fi
}
# while not empty
while [[ (! -z ${next[@]}) ]]; do
    # random pair
    id=$(( (2 * $RANDOM) % ${#next[@]} ))

    s1=${next[$id]} # connected
    s2=${next[$(( $id + 1 ))]} # possibly disconnected

    unset 'next[$id]'
    unset 'next[$(( $id + 1 ))]'
    # shift to avoid empty spaces
    next=(${next[@]})

    if [[ ${allowed[$s2]} = 2 ]]; then
        check $s2

        allowed[$s2]=1
        allowed[$(( ( $s1 + $s2 ) / 2 ))]=1
    fi
done

# show walls in gray
for ((i = 0; i < total; i++)); do
    if [[ ${allowed[$i]} = 0 ]]; then
        tput cup $(( $i / $cols )) $(( 2 * ( $i % $cols ) ))
        echo -ne "\x1b[90;100mww\x1b[39;49m"
    fi
done

# color the end in green
end_y=$(( $rows - 2 ))
end_x=$(( 2 * $cols - 4 ))
tput cup $end_y $end_x
echo -ne "\x1b[32;42mww\x1b[39;49m"

# hide cursor
tput civis

# show the player
tput cup $pos_y $pos_x
echo -ne "\x1b[37;47mww\x1b[39;49m"

move() {
    pos=$(( $pos_y * $cols + $pos_x / 2 ))
    case "$1" in
        0)
            if [ ${allowed[$(( $pos - 1 ))]} = 1 ]; then
                pos_x=$(( $pos_x - 2))
            fi
        ;; # right
        1)
            if [ ${allowed[$(( $pos + 1 ))]} = 1 ]; then
                pos_x=$(( $pos_x + 2))
            fi
        ;; # left
        2)
            if [ ${allowed[$(( $pos - $cols ))]} = 1 ]; then
                pos_y=$(( $pos_y - 1))
            fi
        ;; # up
        3)
            if [ ${allowed[$(( $pos + $cols ))]} = 1 ]; then
                pos_y=$(( $pos_y + 1))
            fi
        ;; # down
    esac
}

# game status
won=0

# game loop
while [[ $q != q && $won = 0 ]]; do
    read -n 1 -s q
    tput cup $pos_y $pos_x
    echo -ne "\x1b[39;49m  " # clears previous position of the player
    case "$q" in
        [aA] ) move 0;;
        [dD] ) move 1;;
        [wW] ) move 2;;
        [sS] ) move 3;;
    esac
    tput cup $pos_y $pos_x
    echo -ne "\x1b[37;47mww\x1b[39;49m"

    if [[ $pos_y = $end_y && $pos_x = $end_x ]]; then
        tput cup $(( $rows / 2)) $(( $cols - 4))
        echo -ne "\x1b[32;49mYou win!\x1b[39;49m"
        won=1
        sleep 2
    fi
done

# show cursor
tput cnorm

clear
