#!/usr/bin/perl

use warnings;

($name) = @ARGV;

open $ILDA, "$name\.txt" or die "Input TXT file not found: $name.txt";
open ($INCLUDE, '>', "$name\.h") or die "Could not open output: $name.h";

$firstPoint = 1;
$field1Start = 0;
$field2Start = 0;
$field1End = 0;
$field2End = 0;

$increment = 200;

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
	if ( $firstPoint ) {
		$firstPoint = 0;
		$field1Start = $field[1] & 0xfff;
		$field2Start = $field[2];
	}
	$field1End = $field[1] & 0xfff;
	$field2End = $field[2];
	printf $INCLUDE "%#x,\n",$fieldXY;
}


while ( $field1Start != $field1End || $field2Start != $field2End ) {

	$fieldDif = abs $field1Start - $field1End;
	if ( $fieldDif >= $increment ) { $fieldDif = $increment; }
	if ( $field1Start > $field1End ) { $field1End += $fieldDif; } else { $field1End -= $fieldDif; }


	$fieldDif = abs $field2Start - $field2End;
	if ( $fieldDif >= $increment ) { $fieldDif = $increment; }
	if ( $field2Start > $field2End ) { $field2End += $fieldDif; } else { $field2End -= $fieldDif; }

        $fieldXY = ($field1End << 16) | ($field2End & 0xffff);
	printf $INCLUDE "%#x,\n",$fieldXY;
}

printf $INCLUDE "};\n";
