


# define VIDEO_ADDRESS 0 xb8000
# define MAX_ROWS 25
# define MAX_COLS 80
// Attribute byte for our default colour scheme .
# define WHITE_ON_BLACK 0 x0f
// Screen device I/O ports
# define REG_SCREEN_CTRL 0 x3D4
# define REG_SCREEN_DATA 0 x3D5

/* Print a char on the screen at col , row , or at cursor position */
void print_char ( char character , int col , int row , char attribute_byte ) {
/* Create a byte ( char ) pointer to the start of video memory */
    unsigned char * vidmem = ( unsigned char *) VIDEO_ADDRESS ;
/* If attribute byte is zero , assume the default style . */
    if (! attribute_byte )
    {
        attribute_byte = WHITE_ON_BLACK ;
    }
/* Get the video memory offset for the screen location */
    int offset ;
/* If col and row are non - negative , use them for offset . */
    if ( col >= 0 && row >= 0) 
    {
        offset = get_screen_offset ( col , row );
/* Otherwise , use the current cursor position . */
    } 
    else 
    {
        offset = get_cursor ();
    }
// If we see a newline character , set offset to the end of
// current row , so it will be advanced to the first col
// of the next row.
    if ( character == ’\n ’) 
    {
        int rows = offset / (2* MAX_COLS );
        offset = get_screen_offset (79 , rows );
// Otherwise , write the character and its attribute byte to
// video memory at our calculated offset .
    } 
    else 
    {
        vidmem [ offset ] = character ;
        vidmem [ offset +1] = attribute_byte ;
    }
// Update the offset to the next character cell
    offset += 2;
// Make scrolling adjustment.
    offset = handle_scrolling ( offset );
// Update the cursor position on the screen device.
    set_cursor ( offset );
}


int get_cursor () {
// The device uses its control register as an index to select its internal registers 
    port_byte_out ( REG_SCREEN_CTRL , 14);
    int offset = port_byte_in ( REG_SCREEN_DATA ) << 8;
    port_byte_out ( REG_SCREEN_CTRL , 15);
    offset += port_byte_in ( REG_SCREEN_DATA );

    return offset *2;
}
void set_cursor (int offset ) 
{
    offset /= 2; // Convert from cell offset to char offset .
}

void print_at ( char * message , int col , int row ) 
{
// Update the cursor if col and row not negative .
    if ( col >= 0 && row >= 0) 
    {
        set_cursor ( get_screen_offset ( col , row ));
    }
// Loop through each char of the message and print it.
    int i = 0;
    while ( message [ i] != 0) 
    {
        print_char ( message [ i ++] , col , row , WHITE_ON_BLACK );
    }
}

void print ( char * message ) 
{
    print_at ( message , -1, -1);
}

void clear_screen () 
{
    int row = 0;
    int col = 0;
/* Loop through video memory and write blank characters . */
    for ( row =0; row < MAX_ROWS ; row ++) {
        for ( col =0; col < MAX_COLS ; col ++) {
            print_char ( ’ ’ , col , row , WHITE_ON_BLACK );
        }
    }
// Move the cursor back to the top left .
    set_cursor ( get_screen_offset (0 , 0));
}


/* Copy bytes from one place to another . */
void memory_copy ( char * source , char * dest , int no_bytes ) 
{
    int i;
    for (i =0; i < no_bytes ; i ++) 
    {
        *( dest + i) = *( source + i );
    }
}

/* Advance the text cursor , scrolling the video buffer if necessary . */
int handle_scrolling ( int cursor_offset ) 
{
// If the cursor is within the screen , return it unmodified .
    if ( cursor_offset < MAX_ROWS * MAX_COLS *2) 
    {
        return cursor_offset ;
    }
/* Shuffle the rows back one . */
    int i;
    for (i =1; i < MAX_ROWS ; i ++) 
    {
        memory_copy ( get_screen_offset (0 , i) + VIDEO_ADDRESS ,
        get_screen_offset (0 ,i -1) + VIDEO_ADDRESS ,
        MAX_COLS *2);
    }
/* Blank the last line by setting all bytes to 0 */
    char * last_line = get_screen_offset (0 , MAX_ROWS -1) + VIDEO_ADDRESS ;
    for (i =0; i < MAX_COLS *2; i ++) 
    {
        last_line [ i] = 0;
    }
    cursor_offset -= 2* MAX_COLS ;
// Return the updated cursor position .
    return cursor_offset ;
}
