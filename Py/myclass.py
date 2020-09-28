
from mypara import MyParaClass


class LinkClass:
    def __init__(self): 
        self.id = -1
        self.cap = -1
        self.flow = -1
        self.cost = -1
        self.t0 = -1
        self.alpha = -1
        self.power = -1
        self.tail = -1
        self.head = -1
        self.vc_ratio = -1

class ODClass:
    def __init__(self): 
        self.id = -1
        self.origin = -1
        self.dest = -1
        self.demand = -1
        self.UECot = -1

class ScenarioClass:
    def __init__(self): 
        self.id = -1
        self.vul_link = -1
        self.ods = []
        self.links = []
        self.RecoverCase = -1
        self.vul_measure = {
            "V/C":-1.0,  # v/c ratio
            "NEI":-1.0,  # network efficiency
            "NRI":-1.0,  # robust index
            "wNRI":-1.0, # weighted NRI
            "NTR":-1.0,  # NRI/total demand
            "UNPM":-1.0, # unified network index
            "EG":-1.0  # used in computing UNPM

        }

    def cal_vc_ratio(self,mp:MyParaClass):
        """
            vc ratio for each links
        """
        for l in self.links:
            if l.id == self.vul_link:
                if mp.para_dict["Procedure"] == "EvalOne":
                    l.vc_ratio = 99
                elif mp.para_dict["Procedure"] == "RecoverOne":
                    l.vc_ratio = l.flow/l.cap
                else:
                    input("Warning: cal NRI, procedure is not specified")
            else:
                l.vc_ratio = l.flow/l.cap
    
    def cal_NRI(self,mp:MyParaClass):
        """
            total cost
        """
        self.vul_measure["NRI"] = 0.0
        for l in self.links:                
            if l.id == self.vul_link:
                if mp.para_dict["Procedure"] == "EvalOne":
                    pass
                elif mp.para_dict["Procedure"] == "RecoverOne":
                    self.vul_measure["NRI"] = self.vul_measure["NRI"] + l.cost*l.flow
                else:
                    input("Warning: cal NRI, procedure is not specified")
            else:
                self.vul_measure["NRI"] = self.vul_measure["NRI"] + l.cost*l.flow
    
    def cal_wNRI(self,_base):
        """
            weighted nri using OD flow 
        """
        up = 0.0
        down = 0.0
        for w in range(0,len(self.ods)):
            wij = self.ods[w].demand
            cij = self.ods[w].UECost
            cij0 = _base.ods[w].UECost
            up = up + wij*(cij-cij0)
            down = down + wij
        self.vul_measure["wNRI"] = up/down

    def cal_EG(self):
        """
           EG for UNPM
        """
        val = 0.0
        for w in self.ods:
            val = val + w.demand/w.UECost
        self.vul_measure["EG"] = val/len(self.ods)

    def cal_UNPM(self,_base):
        """
            UNPM measurements
        """
        self.vul_measure["UNPM"] = (_base.vul_measure["EG"]-self.vul_measure["EG"])/_base.vul_measure["EG"]


    

            


    
