import os
import sys
import subprocess
import time
import signal
import ROOT
import numpy as np
from root_numpy import root2array, rec2array
from functions import *
import pickle

from multiprocessing import Process
from multiprocessing import Pool

def readout_to_numpy_arrays(infilename, treename, outpath, outname):
    infile = ROOT.TFile.Open(infilename)

    myoutpath = outpath + 'MLInput_Reduced/'
    create_path(myoutpath)

    print 'creating numpy arrays for input sample %s' % (outname)
    # Get AnalysisTree
    entries = infile.AnalysisTree.GetEntriesFast()
    # print entries

    tree = infile.Get(treename)
    leaves = tree.GetListOfLeaves()
    unwanted_tags = ['weight_', 'jet4', 'jet5', 'jet6', 'jet7', 'jet8', 'jet9', 'N_bJets_', '_zprime', 'eventweight', '_ele1', 'tau32', 'tau21']
    # more_unwanted_tags = ['tau1', 'tau2', 'tau3', 'ndaughters']
    unwanted_exact_tags = ['n_ele', 'n_mu']
    # unwanted_tags = ['weight_', 'jet7', 'jet8', 'jet9', 'N_bJets_', '_zprime', 'eventweight']
    variables = []
    eventweights = ['eventweight']
    for leaf in leaves:
        write = True
        for tag in unwanted_tags:
            if tag in leaf.GetName(): write = False
        for tag in unwanted_exact_tags:
            if tag == leaf.GetName(): write = False
        if write: variables.append(leaf.GetName())
    print variables

    chunksize = 200000
    maxidx = int(entries/float(chunksize)) + 1
    if entries % chunksize == 0: maxidx -= 1
    print entries, chunksize, maxidx
    for i in range(maxidx):
        mymatrix = root2array(filenames=infilename, treename=treename, branches=variables, start=i*chunksize, stop=(i+1)*chunksize)
        mymatrix = rec2array(mymatrix)
        # print type(mymatrix)
        # print mymatrix[0,:]
        # mymatrix = mymatrix.astype(np.float16)
        # print mymatrix[0,:]
        myweights = root2array(filenames=infilename, treename=treename, branches=eventweights, start=i*chunksize, stop=(i+1)*chunksize)
        myweights = rec2array(myweights)
        # myweights = myweights.astype(np.float16)

        thisoutname = myoutpath + outname + '_' + str(i) + '.npy'
        thisoutname_weights = myoutpath + 'Weights_' + outname + '_' + str(i) + '.npy'
        np.save(thisoutname, mymatrix)
        np.save(thisoutname_weights, myweights)
        percent = float(i+1)/float(maxidx) * 100.
        sys.stdout.write( '{0:d} of {1:d} ({2:4.2f} %) jobs done.\r'.format(i+1, maxidx, percent))
        if not i == maxidx-1: sys.stdout.flush()


    with open(myoutpath + 'variable_names.pkl', 'w') as f:
        pickle.dump(variables, f)





def readout_to_numpy_arrays_reduced(infilename, treename, outpath, outname):
    infile = ROOT.TFile.Open(infilename)

    myoutpath = outpath + 'MLInput_Reduced/'
    create_path(myoutpath)

    print 'creating numpy arrays for input sample %s' % (outname)
    # Get AnalysisTree
    entries = infile.AnalysisTree.GetEntriesFast()
    # print entries

    tree = infile.Get(treename)
    leaves = tree.GetListOfLeaves()
    # unwanted_tags = ['weight_', 'jet4', 'jet5', 'jet6', 'jet7', 'jet8', 'jet9', 'N_bJets_', '_zprime', 'eventweight', '_ele1', 'tau32', 'tau21']
    # unwanted_exact_tags = ['n_ele', 'n_mu']
    variables = []
    eventweights = ['eventweight']
    # for leaf in leaves:
    #     write = True
    #     for tag in unwanted_tags:
    #         if tag in leaf.GetName(): write = False
    #     for tag in unwanted_exact_tags:
    #         if tag == leaf.GetName(): write = False
    #     if write: variables.append(leaf.GetName())
    # print variables
    wanted_tags = ['px_jet', 'py_jet', 'pz_jet', 'e_jet', 'csv_jet', 'px_mu', 'py_mu', 'pz_mu', 'e_mu', 'met_px', 'met_py', 'npv']
    for leaf in leaves:
        write = False
        for tag in wanted_tags:
            if tag in leaf.GetName(): write = True
        if write: variables.append(leaf.GetName())
    print variables
    print len(variables)

    chunksize = 200000
    maxidx = int(entries/float(chunksize)) + 1
    if entries % chunksize == 0: maxidx -= 1
    print entries, chunksize, maxidx
    for i in range(maxidx):
        mymatrix = root2array(filenames=infilename, treename=treename, branches=variables, start=i*chunksize, stop=(i+1)*chunksize)
        mymatrix = rec2array(mymatrix)
        # print type(mymatrix)
        # print mymatrix[0,:]
        # mymatrix = mymatrix.astype(np.float16)
        # print mymatrix[0,:]
        myweights = root2array(filenames=infilename, treename=treename, branches=eventweights, start=i*chunksize, stop=(i+1)*chunksize)
        myweights = rec2array(myweights)
        # myweights = myweights.astype(np.float16)

        thisoutname = myoutpath + outname + '_' + str(i) + '.npy'
        thisoutname_weights = myoutpath + 'Weights_' + outname + '_' + str(i) + '.npy'
        np.save(thisoutname, mymatrix)
        np.save(thisoutname_weights, myweights)
        percent = float(i+1)/float(maxidx) * 100.
        sys.stdout.write( '{0:d} of {1:d} ({2:4.2f} %) jobs done.\r'.format(i+1, maxidx, percent))
        if not i == maxidx-1: sys.stdout.flush()


    with open(myoutpath + 'variable_names.pkl', 'w') as f:
        pickle.dump(variables, f)
