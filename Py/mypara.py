import os
import sys

#*****************************************
is_run_exe = True
# is_run_exe = False
# is_debug_exe = True
is_debug_exe = False
#*****************************************

recover_measure = "NRI"

class MyParaClass:
    def __init__(self): 
        self.para_dict = {
            "OneDimEsp":0.0000001,
            "UEeps":0.001,
            "Network":"SiouxFalls",
            "isWriteConverge":0, # falase, do not write UE converge on screen
            
            # you do not have to change the following parameters
            "Procedure":"Eval_base_and_given_net", # Evaluate the base network first and then the given network
            "Procedure":"Eval_remove_each_one",  # Evaluate the measure for each component by remove
            # "Procedure":"RecoverOne", # Evaluate the recovered one by one
            "WhereToWrite":1   # 0, screen, 1, file, 2, both
            }
        self.release_exe = ""
        self.debug_exe = ""
        self.output_folder = ""
        self.root_folder = ""

    def get_root_folder(self): 
        folder = os.path.abspath(os.path.dirname(__file__)) 
        # print(folder)
        x = folder.split("\\") 
        # print (x)
        self.root_folder = ""
        for i in range(0,len(x)-1):
            if x[i] != "VC":
                self.root_folder = self.root_folder + x[i]+"\\"
            else:
                self.root_folder = self.root_folder +"VC"+"\\"
                break
        self.release_exe = self.root_folder + "x64\\Release\\VC.exe"
        self.debug_exe = self.root_folder + "x64\\Debug\\VC.exe"
        self.output_folder = self.root_folder + "OutPut\\"
        self.input_folder = self.root_folder + "Input\\"


def prn_obj(obj):
    print ('\n'.join(['%s:%s' % item for item in obj.__dict__.items()])) 

