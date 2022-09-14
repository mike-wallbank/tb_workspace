# /nova/app/users/tlackey/TestBeam/textsim.dev/

import math
import numpy
import argparse, textwrap

parser = argparse.ArgumentParser(description='Generate file in hepevt format for TextGen.', formatter_class=argparse.RawTextHelpFormatter)
parser.add_argument('infile', type=str, help=textwrap.dedent('Input file with muon statistics. \n\
Format: vtxX vtxY vtxZ momX momY momZ E'))
parser.add_argument('outfile', type=str, help='Output file intended to be used as input to TextGen job.')
args = parser.parse_args()

outfile = open(args.outfile,'w')
infile = args.infile
#outfile = open('cosmic-evts_dirZ.98.txt','w')


#--------------------------------------------------

def write_event(evtnum, px, py, pz, E, vertx, verty, vertz):
    # Semi-randomly assign mu+ or mu- such that mu+/mu- ~1.1
    # This ratio is accurate for muons that we expect to stop in TestBeam
    # The ratio for the other detectors (especially FarDet) may need adjusting
    if (numpy.random.uniform()>1/2.1):
        pdg=-13
    else:
        pdg=13

    outfile.write("%d 1\n" %(evtnum))
    outfile.write("1 %d 0 0 0 0 %f %f %f %f 0.106 %f %f %f 50000\n" % (pdg, px, py, pz, E, vertx, verty, vertz))

#--------------------------------------------------

def axis_angle_to_Rmatrix(axis, angle):
    """ Convert axis-angle to rotation matrix """
    x,y,z = axis
    #sines
    s = math.sin(angle)
    c = math.cos(angle)

    matrix = numpy.array([[c+pow(x,2)*(1-c), x*y*(1-c)-z*s, x*z*(1-c)+y*s],
                          [x*y*(1-c)+z*s, c+pow(y,2)*(1-c), y*z*(1-c)-x*s],
                          [x*z*(1-c)-y*s, y*z*(1-c)+x*s, c+pow(z,2)*(1-c)]])
    # we only need to rotate back to detector frame
    return numpy.linalg.inv(matrix)
    
#--------------------------------------------------
def main():
    smear = True
    #with open('cosmic-stats-for-sim_dirZ.98.txt','r') as infile:
    with open(infile,'r') as stats:
    #with open('cosmic-stats-for-sim_test.txt','r') as infile:
        lines = stats.readlines()

        evtnum=1

        for line in lines:
            if line.startswith("#"):
                continue
            vertx = float(line.split()[0])
            verty = float(line.split()[1])
            vertz = float(line.split()[2])
            px    = float(line.split()[3])
            py    = float(line.split()[4])
            pz    = float(line.split()[5])
            E     = float(line.split()[6])
            
            write_event(evtnum, px, py, pz, E, vertx, verty, vertz)
            evtnum+=1

            ptot = math.sqrt(pow(px,2)+pow(py,2)+pow(pz,2))

            # theta = azimuthal angle in x-y plane, phi = polar angle from z-axis
            theta = math.atan2(py,px)
            phi = math.acos(pz/ptot)
            
            # find rotation vector
            rot_ang = math.acos(pz/ptot)
            if (px==0 and py==0):
                continue
            rot_axis= 1/math.sqrt(pow(px,2)+pow(py,2))*numpy.array([py, -px, 0])
            Rmatrix=axis_angle_to_Rmatrix(rot_axis, rot_ang)
            orig = numpy.array([[px], [py], [pz]])

            if (smear):
                for i in range(0,19):
                    # 2% spread in momentum
                    mom = numpy.random.normal(ptot,ptot*0.02)
                    # vary theta (azimuthal angle in plane perpendicular to direction of travel) uniformly
                    theta = numpy.random.uniform(0,2*math.pi)
                    #vary phi (polar angle from direction of travel) by 4mrad around 0
                    phi = numpy.random.normal(0,0.004)
                    p_prime = numpy.array([[mom*math.sin(phi)*math.cos(theta)],
                                           [mom*math.sin(phi)*math.sin(theta)],
                                           [mom*math.cos(phi)]])
                    p_vec = numpy.dot(Rmatrix,p_prime)
                    # vary x and y by cell width, z by plane depth
                    x = numpy.random.normal(vertx,4)
                    y = numpy.random.normal(verty,4)
                    z = numpy.random.normal(vertz,6)
                    E  = math.sqrt(pow(0.106,2) + pow(mom,2))
                    
                    write_event(evtnum, p_vec[0,0], p_vec[1,0], p_vec[2,0], E, x, y, z)
                    evtnum+=1

    outfile.close()

#--------------------------------------------------
if __name__ == "__main__":
    # execute only if run as a script
    main()
