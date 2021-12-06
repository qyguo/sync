def main():
 
    print("****Read all lines in file using readlines() *****")    
 
    # Open file    
    #fileHandler = open ("./18112021_ggH_V2.txt", "r")
    #fileHandler_CJST = open ("./22112021_ggH_log.log", "r")
    fileHandler = open ("./diff_18UL_0322_Wm_v2.log", "r")
    fileHandler_CJST = open ("./diff_18UL_0322_Wm_v2.log", "r")

    ##inverse
    ##fileHandler_CJST = open ("./eventList_2017_v10_finalstate_JET_V4_onlyggH.txt", "r")
    ##fileHandler = open ("./CJST/eventlist_all_full_ggHonly_2017_V3.txt", "r")
    
    # Get list of all lines in file
    listOfLines = fileHandler.readlines()
    listOfLines_CJST = fileHandler_CJST.readlines()
    
    # Close file
    fileHandler.close()          
    fileHandler_CJST.close()          
    
    # Iterate over the lines
    index = 0
    line_diff_=""
    for line in listOfLines:
        index+=1
        found_context = False
        if not line.startswith("BBF =>"):    continue
        if "-- [57]=" in line:    continue
        context_ = line.strip().split('=',)
        if len(context_)<4:    continue

        matched=False

        line_CJST=listOfLines_CJST[index]
        if not line_CJST.startswith("LLR =>"):    continue
        #print line_CJST

        context_CJST_ = line_CJST.strip().split('=',)
        if len(context_CJST_)<4:    continue
        Event_Num=bool( context_CJST_[1:3]==context_[1:3] )

        #print line_CJST
        #print line

        if Event_Num:    matched=True
        if not Event_Num:    print("What!!!! not match")
        check_=bool( context_CJST_==context_)
        if Event_Num:
            context_CJST_1=context_CJST_[3].split(':')
            context_1=context_[3].split(':')
            #result =  all(elem in context_CJST_1  for elem in context_[1])
            for ii in range(len(context_1)):
                check_1=bool(round(float(context_CJST_1[ii]))==round(float(context_1[ii])))
                if not check_1:
                    if context_CJST_1[ii] in ('-999.000', '-99.0000', '-1.000', '-1.0000') and context_1[ii] in ('-999.000', '-99.0000', '-1.000', '-1.0000'):
                        check_1=True
                #check_1=bool(float(context_CJST_1[ii])==float(context_1[ii]))
                if not check_1:
                    index_=context_[2].split('[')[1].split(']')[0]
                    if ':' in index_:
                        index_=index_.split(':')[0]
                    index_=int(index_)+ii
                    print('='.join(context_[0:3]).split('[')[0]+'['+str(index_)+']'+context_1[ii])
                    print('='.join(context_CJST_[0:3]).split('[')[0]+'['+str(index_)+']'+context_CJST_1[ii])

        if not matched: 
            print("No events matched here: Run:lumi:Events: {0}:{1}:{1};".format(context_[0], context_[1], context_[2]))

        #if index>10:    break

#            result = all(elem in context_CJST_ for elem in  context_)
#
#            #result =  all(elem in context_CJST_[0:-4] for elem in context_[0:-5])##without eventweigh ##when with final state -1 is used for reduction 
#            result =  all(elem in context_CJST_ for elem in context_[0:-1])##without eventweigh ##when with final state -1 is used for reduction 
#            ###inverse
#            ###result =  all(elem in context_CJST_[0:-5] for elem in context_)##without eventweigh ##when with final state -1 is used for reduction 
#            #result =  all(elem in context_CJST_[0:-4]+context_CJST_[-3:29]  for elem in context_[0:-5]+context_[-4:-1])##without eventweigh ##when with final state -1 is used for reduction 
#            ### compare without met and weigh CJST without MET -2 with MET -3
#            ##result =  all(elem in context_CJST_[0:12]+context_CJST_[23:26] for elem in context_[0:12]+context_[-8:-5])##without eventweigh ##when with final state -1 is used for reduction 
#            #result =  all(elem in context_CJST_  for elem in context_)
#            #result  =  all(elem in context_CJST_  for elem in context_[0:6])
#            result_ = all(elem in context_CJST_  for elem in context_[0:3])
#        #if index==1:  print line.strip().split(':',)[0:12]+line.strip().split(':',)[-8:-5]
#        #if index==1:  print line_diff_.strip().split(':',)[0:12]+line_diff_.strip().split(':',)[23:26]
        #if index>20:    break

if __name__ == '__main__':
    main()
