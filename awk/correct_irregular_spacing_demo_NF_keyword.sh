input_file=test_input/irregular_spacing_correct/input.txt
cat $input_file | awk 'value="";{for(i=1;i<=NF;i++) value = value " " $i;print value;}'
