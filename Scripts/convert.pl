#!/usr/bin/perl

use warnings;

($name) = @ARGV;

open $ILDA, "$name\.txt" or die "Input TXT file not found: $name.txt";
open ($INCLUDE, '>', "$name\.h") or die "Could not open output: $name.h";

printf $INCLUDE "const uint32_t PROGMEM draw_$name\[] = {\n";
while ( <$ILDA> ) {
	@field = split (/\s+/,$_);
	if ( $_ =~ /^frame/ ) {
		$xy = $field[1];	
		next;
	}
	next if ( $_ =~ /^\s*$/ );
	next if ( $_ =~ /^\s*#/ );
	next if ( $_ =~ /palette/ );
	@field = split (/\s+/,$_);
	$field[1] = ($field[1] + 32767)/16;
	if ( $xy eq 'xy' ) {
		if ( $field[3] >= 0 ) { $field[1] |= 0x8000; }
	} else {
		if ( $field[4] >= 0 ) { $field[1] |= 0x8000; }
	}
	$field[2] = ($field[2] + 32767)/16;
	$fieldXY = ($field[1] << 16) | ($field[2] & 0xffff);
	printf $INCLUDE "%#x,\n",$fieldXY;
}

printf $INCLUDE "};\n";
