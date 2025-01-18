cat test_input/find_diff_with_prev_line/input.txt | awk 'BEGIN{first_line=1;prev=0} {if (!first_line) print ($1-prev);prev=$1;first_line=0}'
