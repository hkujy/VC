
"""
    write the test scrips
"""
import os
import shutil

#
para_dict={
"TestIndex":1,     # 0, enueration, 1 CSA and GA
"OneDimEsp":0.0000001,
"UEeps":0.0001,
"UEmaxIter":5000,
"MaxNumSol":20000,
"StopCriteria":1,
"Network":"Anaheim",
"isWriteConverge":0,
"WhereToWrite":1,   # 0, screen, 1, file, 2, both
"CsaNumPop":10,
"CsaCloneBeta":0.9,
"CsaRepRatio":0.1,
"MaxCsaIter":500,
"GANumPop":10,
"GANumChild":10,
"GaMutationRate":0.1,
"MaxGAIter":500
}

run = r"c:/GitCodes/ResiV2/x64/Release/NetworkResilience.exe"

def Test_Max_UESol():
    """
        test the effect of maximum number of UE solutions
    """
    para_dict["MaxNumSol"] = 10000
    para_dict["isWriteConverge"] = 0    # 0: false, 1 ture
    para_dict["WhereToWrite"] = 1       # file
    para_dict["UEeps"] = 0.0001
    #--------------------------------------------------
    with open("c:/GitCodes/ResiV2/InPut/Para.txt","w+") as f:
        for i in para_dict:
            print("{0},{1}".format(i,para_dict[i]),file = f)
    os.system(run)
    
    copydir = r"c:/GitCodes/ResiV2/Py/MaxSol_10000"
    if os.path.isdir(copydir):
        shutil.rmtree(copydir)
    shutil.copytree(r"c:/GitCodes/ResiV2/OutPut/",copydir)
    #--------------------------------------------------
    para_dict["MaxNumSol"] = 20000
    with open("c:/GitCodes/ResiV2/InPut/Para.txt","w+") as f:
        for i in para_dict:
            print("{0},{1}".format(i,para_dict[i]),file = f)
    os.system(run)
    copydir = r"c:/GitCodes/ResiV2/Py/MaxSol_20000"
    if os.path.isdir(copydir):
        shutil.rmtree(copydir)
    shutil.copytree(r"c:/GitCodes/ResiV2/OutPut/",copydir)
    #--------------------------------------------------
    para_dict["MaxNumSol"] = 30000
    with open("c:/GitCodes/ResiV2/InPut/Para.txt","w+") as f:
        for i in para_dict:
            print("{0},{1}".format(i,para_dict[i]),file = f)
    os.system(run)

    copydir = r"c:/GitCodes/ResiV2/Py/MaxSol_30000"
    if os.path.isdir(copydir):
        shutil.rmtree(copydir)
    shutil.copytree(r"c:/GitCodes/ResiV2/OutPut/",copydir)

    #--------------------------------------------------
    para_dict["MaxNumSol"] = 40000
    with open("c:/GitCodes/ResiV2/InPut/Para.txt","w+") as f:
        for i in para_dict:
            print("{0},{1}".format(i,para_dict[i]),file = f)
    os.system(run)

    copydir = r"c:/GitCodes/ResiV2/Py/MaxSol_40000"
    if os.path.isdir(copydir):
        shutil.rmtree(copydir)
    shutil.copytree(r"c:/GitCodes/ResiV2/OutPut/",copydir)

  #--------------------------------------------------
    para_dict["MaxNumSol"] = 50000
    with open("c:/GitCodes/ResiV2/InPut/Para.txt","w+") as f:
        for i in para_dict:
            print("{0},{1}".format(i,para_dict[i]),file = f)
    os.system(run)

    copydir = r"c:/GitCodes/ResiV2/Py/MaxSol_50000"
    if os.path.isdir(copydir):
        shutil.rmtree(copydir)
    shutil.copytree(r"c:/GitCodes/ResiV2/OutPut/",copydir)


def Test_Toler():
    """
        test the tolerance
    """
    para_dict["Network"] = "SiouxFalls"
    para_dict["TestIndex"] = 0
    para_dict["MaxNumSol"] = 10000
    #--------------------------------------------------
    para_dict["UEeps"] = 0.01
    # para_dict["UEeps"] = 0.000001
    with open("c:/GitCodes/ResiV2/InPut/Para.txt","w+") as f:
        for i in para_dict:
            print("{0},{1}".format(i,para_dict[i]),file = f)
    os.system(run)
    copydir = r"c:/GitCodes/ResiV2/Py/toler01"
    if os.path.isdir(copydir):
        shutil.rmtree(copydir)
    shutil.copytree(r"c:/GitCodes/ResiV2/OutPut/",copydir)
    # os.system("PAUSE")
    #--------------------------------------------------
    para_dict["UEeps"] = 0.001
    with open("c:/GitCodes/ResiV2/InPut/Para.txt","w+") as f:
        for i in para_dict:
            print("{0},{1}".format(i,para_dict[i]),file = f)
    os.system(run)
    copydir = r"c:/GitCodes/ResiV2/Py/toler001"
    if os.path.isdir(copydir):
        shutil.rmtree(copydir)
    shutil.copytree(r"c:/GitCodes/ResiV2/OutPut/",copydir)
    #--------------------------------------------------
    para_dict["UEeps"] = 0.0001
    with open("c:/GitCodes/ResiV2/InPut/Para.txt","w+") as f:
        for i in para_dict:
            print("{0},{1}".format(i,para_dict[i]),file = f)
    os.system(run)

    copydir = r"c:/GitCodes/ResiV2/Py/toler0001"
    if os.path.isdir(copydir):
        shutil.rmtree(copydir)
    shutil.copytree(r"c:/GitCodes/ResiV2/OutPut/",copydir)
    #--------------------------------------------------
    para_dict["UEeps"] = 0.00001
    with open("c:/GitCodes/ResiV2/InPut/Para.txt","w+") as f:
        for i in para_dict:
            print("{0},{1}".format(i,para_dict[i]),file = f)
    os.system(run)
    copydir = r"c:/GitCodes/ResiV2/Py/toler00001"
    if os.path.isdir(copydir):
        shutil.rmtree(copydir)
    shutil.copytree(r"c:/GitCodes/ResiV2/OutPut/",copydir)
    #--------------------------------------------------
    para_dict["UEeps"] = 0.000001
    with open("c:/GitCodes/ResiV2/InPut/Para.txt","w+") as f:
        for i in para_dict:
            print("{0},{1}".format(i,para_dict[i]),file = f)
    os.system(run)
    copydir = r"c:/GitCodes/ResiV2/Py/toler000001"
    if os.path.isdir(copydir):
        shutil.rmtree(copydir)
    shutil.copytree(r"c:/GitCodes/ResiV2/OutPut/",copydir)

def Test_Converge():

    """
        test the effect of maximum number of UE solutions
    """
    para_dict["MaxNumSol"] = 10000
    para_dict["isWriteConverge"] = 1    # 0: false, 1 True
    para_dict["WhereToWrite"] = 1       # file
    # para_dict["UEeps"] = 0.1
    para_dict["UEeps"] = 0.0001
    #--------------------------------------------------
    with open("c:/GitCodes/ResiV2/InPut/Para.txt","w+") as f:
        for i in para_dict:
            print("{0},{1}".format(i,para_dict[i]),file = f)
    os.system(run)
    
    copydir = r"c:/GitCodes/ResiV2/Py/Converge_10000"
    if os.path.isdir(copydir):
        shutil.rmtree(copydir)
    shutil.copytree(r"c:/GitCodes/ResiV2/OutPut/",copydir)
    #--------------------------------------------------
    print("**************************************************************************************************************")
    print("This computer only output the convergence curve, So I need to copy the script and results back to the original")
    print("**************************************************************************************************************")
    
 


if __name__== "__main__":
    # Test_Toler()
    # Test_Max_UESol()
    Test_Converge()


