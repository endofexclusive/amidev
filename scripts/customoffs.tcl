# The script returns a list of {regname offs} pairs.

# Generate COLOR00..COLOR31
proc coloroffss {} {
        for {set i 0} {$i < 32} {incr i} {
                lappend offss "[format "color%02d" $i] [expr {0x180+$i*2}]"
        }
        return $offss
}

return \
        "{diwstrt 0x08e} \
        {diwstop 0x090} \
        {ddfstrt 0x092} \
        {ddfstop 0x094} \
        {bplcon0 0x100} \
        {bplcon1 0x102} \
        {bpl1mod 0x108} \
        {bpl2mod 0x10a} \
        [coloroffss]"

