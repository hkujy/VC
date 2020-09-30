
import networkx as nx
import pandas as pd
import numpy as np
import random
import matplotlib; matplotlib.use('TkAgg')
import matplotlib.pyplot as plt
import flow_measure as FM
import flow_measure as FM
import mypara as mp
# state of critical functionality (SCF) defined as the ratio of
# functionality at a given instance during the restoration process [instantaneous functionality (IF)]
# to a state of functionality before perturbation [target functionality (TF)].
# SCF = 1 represents a fully functional system, whereas SCF = 0 represents the total loss of functionality.
# The measure here uses the size of the largest connected component (LCC)

# for edge recovery sequencing, the following metrics can be used as the criterion:
# edge betweenness centrality
# average of head and tail nodes' degree centrality
# average of head and tail nodes' closeness centrality
# average of head and tail nodes' closeness centrality


def gen_graph (dt):
    G = nx.DiGraph()
    for i in range(len(dt)):
        G.add_nodes_from([dt.iloc[i][0],dt.iloc[i][1]])
        G.add_edge(dt.iloc[i][0],dt.iloc[i][1], length = dt.iloc[i][2])

    nx.set_edge_attributes(G, 1, 'weight') # future use as a simple graph

    print(nx.info(G))
    fig = plt.figure(figsize=(10, 9))
    pos = nx.planar_layout(G)
    nx.draw_networkx(G, pos=pos)
    fig.savefig('SF_network.png', dpi=fig.dpi)
    return G

def network_disrupt_repair(edges, G, method, connection='strong'):
    H = nx.DiGraph()
    H = G.copy()
    TF = cal_TF(G, connection)
    H = disrupt_network_edge(H, edges)
    sorted_edges = sort_edges(edges, method, G)
    results = repair(H, sorted_edges, TF, connection)
    return results

def cal_TF(G, connection):
    if connection=='strong':
        return len(max(nx.strongly_connected_components(G), key=len))
    else:
        return len(max(nx.weakly_connected_components(G), key=len))

def cal_SCF(H, TF, connection):
    if connection=='strong':
        return len(max(nx.strongly_connected_components(H), key=len))/TF
    else:
        return len(max(nx.weakly_connected_components(H), key=len))/TF

def generate_edge_failure(G, number): #number is the total number of disrupted links, random disruotion mechanism here.
    random_edges = random.sample(G.edges(),k=number)
    return random_edges

def disrupt_network_edge(H, edges): #edges is the list of disrupted links (list of tuples)
    H.remove_edges_from(edges)
    fig = plt.figure(figsize=(10, 9))
    pos = nx.planar_layout(H)
    nx.draw_networkx(H, pos=pos)
    fig.savefig('SF_network_disrupted.png', dpi=fig.dpi)
    return H

def sort_edges(edges, method, G):  # edges here is a list of tuples, a list of disrupted links
    if method=='degree_centrality':
        nx.set_node_attributes(G, nx.degree_centrality(G), 'degree_centrality')
        sorted_edges = sorted(edges, key=lambda x: (G.nodes[x[0]]['degree_centrality'] + G.nodes[x[1]]['degree_centrality'])/2.0, reverse=True)
    elif method=='eigenvector_centrality':
        nx.set_node_attributes(G, nx.eigenvector_centrality(G, weight='weight'), 'eigenvector_centrality')
        sorted_edges = sorted(edges, key=lambda x: (G.nodes[x[0]]['eigenvector_centrality'] + G.nodes[x[1]]['eigenvector_centrality'])/2.0, reverse=True)
    elif method=='closeness_centrality':
        nx.set_node_attributes(G, nx.closeness_centrality(G, distance = 'length'), 'closeness_centrality')
        sorted_edges = sorted(edges, key=lambda x: (G.nodes[x[0]]['closeness_centrality'] + G.nodes[x[1]]['closeness_centrality'])/2.0, reverse=True)
    else:
        nx.set_edge_attributes(G, nx.edge_betweenness_centrality(G, weight='length'), 'edge_betweenness_centrality')
        sorted_edges = sorted(edges, key=lambda x: G.adj[x[0]][x[1]]["edge_betweenness_centrality"], reverse=True)
    return sorted_edges

def repair(H, sorted_edges, TF, connection):
    iterations = {}
    iterations['IF'] = cal_SCF(H, TF, connection)  # disrupted network without recovery yet
    for e in sorted_edges:
        if H.has_edge(*e)==False:
            H.add_edge(*e)
            iterations[e] = cal_SCF(H, TF, connection)
        else:
            continue
    return iterations




if __name__== "__main__":
    
    
    disrupt_links = [11,12] 
     
    # test_method = "Eval_remove_each_one"
    test_method = "Eval_base_and_given_net"

    FM.main_func(disrupt_links,test_method)
    
    exit() 
    # dt = pd.read_csv("/Users/wangyi/Documents/Projects/WithYuJiang/Code/edge_list.csv")  #source/target/length
    dt = pd.read_csv("edge_list.csv")  #source/target/length
    G = gen_graph(dt)
    random_edges = generate_edge_failure(G, 40)
    # if this is too few, the LCC can remain 1, since the network is still well connected.
    print('Disrupted edges include:\n', random_edges)

    df = pd.DataFrame(list(network_disrupt_repair(random_edges, G, 'edge_betweenness_centrality').items()))
    # sequencing can be based on ['degree_centrality', 'eigenvector_centrality', 'edge_betweenness_centrality','closeness_centrality']
    df.columns = ['Recovery sequence', 'edge_betweenness_centrality']
    print (df)



    # compute the flow measures



    # For plotting
    df1 = pd.DataFrame(list(network_disrupt_repair(random_edges, G, 'eigenvector_centrality').items()))
    df2 = pd.DataFrame(list(network_disrupt_repair(random_edges, G, 'closeness_centrality').items()))
    df3 = pd.DataFrame(list(network_disrupt_repair(random_edges, G, 'degree_centrality').items()))
    df1.columns = ['Recovery sequence_2', 'eigenvector_centrality']
    df2.columns = ['Recovery sequence_3', 'closeness_centrality']
    df3.columns = ['Recovery sequence_4', 'degree_centrality']

    ax = df.plot(kind='line',y='edge_betweenness_centrality',color='blue',figsize=(20,10))
    df1.plot(kind='line',color='red', ax=ax)
    df2.plot(kind='line',color='green', ax=ax)
    df3.plot(kind='line',color='yellow', ax=ax)
    plt.xlabel('Recovery steps')
    plt.ylabel('State of Critical Functionality')
    ax = plt.gca()
    plt.xticks(np.arange(len(df)), rotation=45)
    plt.savefig('Recovery sequencing comparison.png')
    # The ax is different for each recovery strategy, too messy to show
    # ax.set_xticklabels(df.iteration_1)




