#!/usr/bin/perl

use warnings;
use strict;

use constant ERROR => "Usage for call class.pl:\n",
			"perl class.pl <classname>\n";

my ($option, $class_name);

if(@ARGV == 1) {				# Es gibt genau einen Parameter
	$class_name = $ARGV[0];		# Klassenname als einziger Parameter
} else {
	die ERROR;
}

# Open file .h
open H_FILE, ">\L$class_name.h" or die $!;
# Set content of file .h
print H_FILE "#ifndef __", "\U$class_name", "_H_\n";
print H_FILE "#define __", "\U$class_name", "_H_\n\n\n";
print H_FILE "//INCLUDES\n\n\n";
print H_FILE "class $class_name {\n\n";
print H_FILE "public:\n";
print H_FILE "\t// Standard-Konstruktor\n";
print H_FILE "\t$class_name();\n";
print H_FILE "\t// Destruktor\n";
print H_FILE "\t~$class_name();\n\n";
print H_FILE "private:\n\n";
print H_FILE "};\n\n";
print H_FILE "#endif";
# Close file .h
close H_FILE;

# Open file .cc
open CC_FILE, ">\L$class_name.cc" or die $!;
# Set content of file .cc
print CC_FILE "#include ", '"', "\L$class_name.h", '"', "\n\n";
print CC_FILE "// Standard-Konstruktor\n";
print CC_FILE "$class_name", "::", "$class_name() {\n\n}\n\n";
print CC_FILE "// Destruktor\n";
print CC_FILE "$class_name", "::", "~$class_name() {\n\n}\n\n";
# Close file .h
close CC_FILE;
