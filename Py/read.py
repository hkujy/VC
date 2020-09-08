from cmath import e
from unittest import case
from networkx.algorithms.flow.mincost import cost_of_flow
import pandas as pd
import myclass
import mypara


def read_link(mp:mypara.MyParaClass, _cs):
    """
        read link data
    """
    source_file  = mp.root_folder + "Output\\Link.csv"
    print("read link output file : {0}".format(source_file))
    df = pd.read_csv(source_file)
    num_of_row = df.shape[0]
    _cs.append(myclass.ScenarioClass())
    _cs[-1].id = 0
    _cs[-1].vul_link = -1
    for r in range(0, num_of_row):
        VulLink = df["VulLink"][r]
        link_id = df["ID"][r]
        Tail = df["Tail"][r]
        Head = df["Head"][r]
        Flow = df["Flow"][r]
        Cap = df["Cap"][r]
        Alpha = df["Alpha"][r]
        Beta = df["Beta"][r]
        Cost = df["Cost"][r]
        T0 =  df["T0"][r]
        if VulLink == _cs[-1].vul_link:
            pass
        else:
            _cs.append(myclass.ScenarioClass())
            _cs[-1].vul_link = VulLink
            _cs[-1].id = _cs[-2].id + 1
        _cs[-1].links.append(myclass.LinkClass())
        _cs[-1].links[-1].id = link_id
        _cs[-1].links[-1].cap = Cap
        _cs[-1].links[-1].flow = Flow
        _cs[-1].links[-1].t0  = T0
        _cs[-1].links[-1].alpha = Alpha
        _cs[-1].links[-1].tail = Tail
        _cs[-1].links[-1].head = Head
        _cs[-1].links[-1].power = Beta
        _cs[-1].links[-1].cost = Cost
        # mypara.prn_obj(_cs[-1].links[-1])
    pass

def read_od(mp:mypara.MyParaClass,_cs):
    """
        read od data
    """
    source_file  = mp.root_folder + "Output\\OD.csv"
    df = pd.read_csv(source_file)
    num_of_row = df.shape[0]
    print("read OD output file : {0}".format(source_file))
    cid = 0
    for r in range(0, num_of_row):
        VulLink = df["VulLink"][r]
        Origin = df["Origin"][r]
        Dest = df["Dest"][r]
        ODindex = df["ODIndex"][r]
        Demand = df["Demand"][r]
        UECost = df["UECost"][r]
        if _cs[cid].vul_link == VulLink:
            pass
        else:
            cid = cid + 1
            if _cs[cid].vul_link != VulLink:
                print("Warning: The case vul link and id do not match")
        _cs[cid].ods.append(myclass.ODClass())
        _cs[cid].ods[-1].id = ODindex
        _cs[cid].ods[-1].origin = Origin
        _cs[cid].ods[-1].dest = Dest
        _cs[cid].ods[-1].demand = Demand
        _cs[cid].ods[-1].UECost = UECost
        # mypara.prn_obj(_cs[cid].ods[-1])

    pass

def main(mp:mypara.MyParaClass):
    """
        read data main
    """
    cases = []
    # remark: must read link first,this is how the cases list is first built
    read_link(mp,cases)
    read_od(mp,cases)

    return cases


