Used to fix the 3rd row in found in the city .dat files.

The 3rd and 4th row could be randomly merged.

This program fixes the file balancing the colomns out.

A .dat file must be turned into a csv file for this to work.

use regex to turn .dat fliles into csv format.

using regex:
    Note: Remove qutes from commands.

    Remove first character from every row command:
        Find .^
        Replace ""
    Replace spaces with "," command:
        Find " "+
        Replace ","