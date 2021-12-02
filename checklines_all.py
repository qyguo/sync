def main():
 
    print("****Read all lines in file using readlines() *****")    
 
    # Open file    
    fileHandler = open ("./106X_2018UL_30112021_ttH.txt", "r")
    fileHandler_CJST = open ("./ttH.txt", "r")

    ##inverse
    ##fileHandler_CJST = open ("./eventList_2017_v10_finalstate_JET_V4_onlyggH.txt", "r")
    ##fileHandler = open ("./CJST/eventlist_all_full_ggHonly_2017_V3.txt", "r")
    
    # Get list of all lines in file
    listOfLines = fileHandler.readlines()
    listOfLines_CJST = fileHandler_CJST.readlines()
    
    # Close file
    fileHandler.close()          
    fileHandler_CJST.close()          
    
    N_BBF_nonZero=0
    N_CJST_nonZero=0
    N_BBF_FS=0
    N_CJST_FS=0
    for line in listOfLines:
        context = line.strip().split(':',)
        if  len(context)>3:
            if float(context[56])>0:    N_BBF_nonZero+=1
            if float(context[3])>0:    N_BBF_FS+=1
    for line in listOfLines_CJST:
        context = line.strip().split(':',)
        if  len(context)>3:
            if float(context[56])>0:    N_CJST_nonZero+=1
            if float(context[3])>0:    N_CJST_FS+=1

    print ("Number of fiducial events; passedFullSelection;")
    print ("BBF : ", N_BBF_nonZero, N_BBF_FS)
    print ("CJST: ", N_CJST_nonZero, N_CJST_FS)

    # Iterate over the lines
    index = 0
    line_diff_=""
    for line in listOfLines:
        #index+=1
        found_context = False
        context_ = line.strip().split(':',)
        if len(context_)<3:    continue

        matched=False
        for line_CJST in listOfLines_CJST:
            context_CJST_ = line_CJST.strip().split(':',)
            if len(context_CJST_)<3:    continue

            Event_Num=bool( context_CJST_[0:3]==context_[0:3] )
            if Event_Num: 
                matched=True
                check_1=bool( context_CJST_[0:27]==context_[0:27] )
                check_2=False
                if float(context_CJST_[27])<0 and float(context_[27])==0:    check_2=True
                elif float(context_CJST_[3])<0 and float(context_[3])<0:    check_2=True ## njets not passFullSelection LLR -1
                else:    check_2=bool( float(context_CJST_[27])==float(context_[27]) )
                check_3=False
                if context_CJST_[56]=='0' and context_[56]=='0':    check_3=True #weight not passedFiducial GENmass4l Z1 Z2 BBF -1.0
                else:    check_3=bool( context_CJST_[28:31]==context_[28:31] )
                check_4=bool( context_CJST_[31:57]==context_[31:57] )
                #check_4=bool( round(float(context_CJST_[57]), 2)==float(context_[57]) )##weight
                check_5=bool( context_CJST_[57]==context_[57] )##weight
                check_6=bool( context_CJST_[58:88]==context_[58:88] )


                if not check_1:
                    print("BBF => Run:lumi:Events={0} -- [3:27]={1}".format(':'.join(context_[0:3]), ':'.join(context_[3:27])))
                    print("LLR => Run:lumi:Events={0} -- [3:27]={1}".format(':'.join(context_CJST_[0:3]), ':'.join(context_CJST_[3:27])))
                if not check_2:
                    print("BBF => Run:lumi:Events={0} -- [27]={1}".format(':'.join(context_[0:3]), context_[27]))
                    print("LLR => Run:lumi:Events={0} -- [27]={1}".format(':'.join(context_CJST_[0:3]), context_CJST_[27]))
                if not check_3:
                    print("BBF => Run:lumi:Events={0} -- [28:31]={1}".format(':'.join(context_[0:3]), ':'.join(context_[28:31])))
                    print("LLR => Run:lumi:Events={0} -- [28:31]={1}".format(':'.join(context_CJST_[0:3]), ':'.join(context_CJST_[28:31])))
                if not check_4:
                    print("BBF => Run:lumi:Events={0} -- [31:57]={1}".format(':'.join(context_[0:3]), ':'.join(context_[31:57])))
                    print("LLR => Run:lumi:Events={0} -- [31:57]={1}".format(':'.join(context_CJST_[0:3]), ':'.join(context_CJST_[31:57])))
                if float(context_CJST_[3])>0 and not check_5:
                    print("BBF => Run:lumi:Events={0} -- [57]={1}".format(':'.join(context_[0:3]), context_[57]))
                    print("LLR => Run:lumi:Events={0} -- [57]={1}".format(':'.join(context_CJST_[0:3]), context_CJST_[57]))
                if not check_6:
                    print("BBF => Run:lumi:Events={0} -- [58:88]={1}".format(':'.join(context_[0:3]), ':'.join(context_[58:88])))
                    print("LLR => Run:lumi:Events={0} -- [58:88]={1}".format(':'.join(context_CJST_[0:3]), ':'.join(context_CJST_[58:88])))

                    #index+=1
                break
        if not matched: 
            print("No events matched here: Run:lumi:Events: {0}:{1}:{1};".format(context_[0], context_[1], context_[2]))


if __name__ == '__main__':
    main()
