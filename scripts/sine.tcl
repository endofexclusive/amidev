#!/usr/bin/tclsh
#
# This command is used to generate sinus tables. The output format is C source
# code.

set usage "$::argv0 PERIOD AMPLITUDE"
if { $::argc < 2 } {
        puts "USAGE: $usage"
        exit -1
}

set per [lindex $::argv 0]
set amp [lindex $::argv 1]

set PI 3.1415926535897931

for {set i 0} {$i < $per} {incr i} {
        set r [expr {2.0 * ${PI} * ${i} / ${per}}]
        set v [expr {round($amp * sin($r))}]
        lappend table $v
}

set name "sin${per}x${amp}"
set uname [string toupper ${name}]
puts "#ifndef ${uname}_H_"
puts "#define ${uname}_H_"
puts ""
puts "/* Sine table with period $per and amplitude $amp. */"
puts ""
puts "#include <stdint.h>"
puts ""
puts -nonewline "static const uint8_t $name\[\] = {"
set i 0
foreach v $table {
        if {0 == ($i % 8)} {
                puts ""
                puts -nonewline "       "
        }
        set hval [string range [format "%02x" $v] end-1 end]
        puts -nonewline " 0x${hval}"
        if {$i < $per-1} {
                puts -nonewline ","
        }
        incr i
}
puts ""
puts "};"
puts ""
puts "#endif"
puts ""

