def main():
 
    print("****Read all lines in file using readlines() *****")    
 
    # Open file    
    fileHandler = open ("./05112021_GEN.log", "r")
    fileHandler_CJST = open ("./CJLSTevents_gen.txt", "r")

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
    for line in listOfLines:
        context = line.strip().split(':',)
        if  len(context)>3:
            if float(context[-1])>0:    N_BBF_nonZero+=1
    for line in listOfLines_CJST:
        context = line.strip().split(':',)
        if  len(context)>3:
            if float(context[-1])>0:    N_CJST_nonZero+=1

    print ("Number of fiducial events")

    print ("BBF : ", N_BBF_nonZero)
    print ("CJST: ", N_CJST_nonZero)

    # Iterate over the lines
    index = 0
    line_diff_=""
    for line in listOfLines:
        index+=1
        found_context = False
        context_ = line.strip().split(':',)
        if len(context_)<3:    continue
        #if float(context_[3])<0:    continue
        #print len(context_)
        for line_CJST in listOfLines_CJST:
            context_CJST_ = line_CJST.strip().split(':',)
            if len(context_CJST_)<3:    continue
            #if float(context_CJST_[3])<0:    continue

            Event_Num=bool( context_CJST_[0:3]==context_[0:3] )
            check___=bool( context_CJST_[0:-2]==context_[0:-2] )
            check__1=bool( context_CJST_[3:6]==context_[3:6] )
            check__2=bool( context_CJST_[6:30]==context_[6:30] )
            check__3=bool( context_CJST_[-1]==context_[-1] )
            check__4=bool( context_CJST_[-2]==context_[-2] )
            #Fiducial_or=bool( bool(int(float(context_CJST_[-1])))==bool(int(context_[-1])) )
            #Gen4lZ1Z2=bool(context_CJST_[24:27]==context_[24:27] )
            #mass4l_notZeroBoth=(float(context_CJST_[3])>0 and float(context_[3])>0)
            
            if Event_Num and not check___: 
                ##ignore the difference from approximate
                check_11 = bool(abs(float(context_CJST_[3])-float(context_[3]))>0.000101)
                check_12 = bool(abs(float(context_CJST_[4])-float(context_[4]))>0.000101)
                check_13 = bool(abs(float(context_CJST_[5])-float(context_[5]))>0.000101)
                if not check__1 and (check_11 or check_12 or check_13):
                    print abs(float(context_CJST_[5])-float(context_[5]))
                    print ("BBF  : ",line)
                    print ("LLR  : ",line_CJST)
                elif not (check__2 and check__3):
                    print ("BBF  : ",line)
                    print ("LLR  : ",line_CJST)
                elif (float(context_CJST_[-2])>0 and not check__4):
                    print ("BBF  : ",line)
                    print ("LLR  : ",line_CJST)

            if Event_Num:    continue


if __name__ == '__main__':
    main()
