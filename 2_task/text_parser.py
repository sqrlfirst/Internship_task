

def parse_txt(in_filename, out_filename):
    '''
    Func description 
    '''

    in_file = open(in_filename, mode="r", encoding="utf-8")
    out_file = open(out_filename, mode="a", encoding="utf-8")

    result_dict = {}

    # read input file by lines and put it to dictionary 
    for line in in_file:
        line = line[:-1].split(' ')
        name, req_per_hour, hours, info = line
        req_per_hour = int(req_per_hour)
        hours = int(hours)

        if name in result_dict:
            # add to existing values
            result_dict[name][0] += req_per_hour           
            result_dict[name][1] += hours                  
            result_dict[name][2] += req_per_hour * hours    
        else:
            # add keys
            result_dict[name] = [req_per_hour, hours, req_per_hour*hours, info]

    #sort dict by keys and transform it to list of lists
    sorted_result = sorted(result_dict.items(), key=lambda x: x[0])
    
    #write result to file                                      
    result_string = ""
    for result in sorted_result:
        name, data = result
        req_per_h_total = str(data[0]) + ' '
        hour_total      = str(data[1]) + ' '
        req_total       = str(data[2]) + ' '
        info            = str(data[3]) + '\n'
        result_string += name + " " + req_per_h_total + hour_total + req_total + info
    
    result_string -= '\n'

    out_file.write(result_string)




if __name__ == '__main__':
    in_txt = str(input('Enter name of file for processing: '))
    out_txt = str(input('Enter name of file for saving result: '))
    
    parse_txt(in_txt, out_txt)


# testing results 6.6s fo 10m lines .txt