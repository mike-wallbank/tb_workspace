# Simple script to read in particle properties and smear the
# distributions to produce more examples from the sample events.
# Mike Wallbank

# The math was diligently worked through by Teresa and was
# adapted (or rather, blatantly copied) from
# CosmicStudies/generate_hepevt_cosmic.py.

import math
import numpy
import argparse, textwrap

parser = argparse.ArgumentParser(description="Smear particles which are already in the TextGen input format")
parser.add_argument("infile", type=str,
                    help="Input file in TextGen format")
parser.add_argument("outfile", type=str,
                    help="Output file to be written in TextGen format")
parser.add_argument("--nsmear", type=int, default=10,
                    help="Number of particles with smeared properties to create from each input particle")
parser.add_argument("--momentum", type=float, default=5.,
                    help="Momentum smearing [%%]; default 5.0")
parser.add_argument("--theta", type=float, default=4.,
                    help="Theta (angle from z-axis) smearing [mrad]; default 4.0")
parser.add_argument("--x", type=float, default=4.,
                    help="X position smearing [cm]; default 4.0")
parser.add_argument("--y", type=float, default=4.,
                    help="Y position smearing [cm]; default 4.0")
parser.add_argument("--z", type=float, default=6.,
                    help="Z position smearing [cm]; default 6.0")
args = parser.parse_args()

#--------------------------------------------------
def axis_angle_to_Rmatrix(axis, angle):
    """ Convert axis-angle to rotation matrix """

    x,y,z = axis

    s = math.sin(angle)
    c = math.cos(angle)

    matrix = numpy.array([[c+pow(x,2)*(1-c), x*y*(1-c)-z*s, x*z*(1-c)+y*s],
                          [x*y*(1-c)+z*s, c+pow(y,2)*(1-c), y*z*(1-c)-x*s],
                          [x*z*(1-c)-y*s, y*z*(1-c)+x*s, c+pow(z,2)*(1-c)]])

    # we only need to rotate back to detector frame
    return numpy.linalg.inv(matrix)
    
#--------------------------------------------------
def main():

    outFile = open(args.outfile, 'w')
    event_num = 0

    for line in open(args.infile, 'r'):

        if line.startswith("#"):
            continue

        line_split = line.split()
        if len(line_split) == 2:
            continue

        status    = int(line_split[0])
        pdg       = int(line_split[1])
        mother1   = int(line_split[2])
        mother2   = int(line_split[3])
        daughter1 = int(line_split[4])
        daughter2 = int(line_split[5])
        px        = float(line_split[6])
        py        = float(line_split[7])
        pz        = float(line_split[8])
        energy    = float(line_split[9])
        mass      = float(line_split[10])
        vx        = float(line_split[11])
        vy        = float(line_split[12])
        vz        = float(line_split[13])
        time      = float(line_split[14])

        ptot = math.sqrt(pow(px,2)+pow(py,2)+pow(pz,2))

        # phi = azimuthal angle in x-y plane, theta = polar angle from z-axis
        phi = math.atan2(py,px)
        theta = math.acos(pz/ptot)
            
        # find rotation vector
        rot_ang = math.acos(pz/ptot)
        if (px == 0 and py == 0):
            continue
        rot_axis = 1/math.sqrt(pow(px,2)+pow(py,2))*numpy.array([py, -px, 0])
        Rmatrix = axis_angle_to_Rmatrix(rot_axis, rot_ang)
        orig = numpy.array([[px], [py], [pz]])

        for smear_event in range(args.nsmear):

            # smear the momentum
            mom = numpy.random.normal(ptot, ptot*0.01*args.momentum)

            # vary phi (azimuthal angle in plane perpendicular to direction of travel) uniformly
            phi = numpy.random.uniform(0, 2*math.pi)

            # vary theta (polar angle from direction of travel) around 0
            theta = numpy.random.normal(0, 1.e-3*args.theta)

            p_prime = numpy.array([[mom*math.sin(theta)*math.cos(phi)],
                                   [mom*math.sin(theta)*math.sin(phi)],
                                   [mom*math.cos(theta)]])
            p_vec = numpy.dot(Rmatrix, p_prime)

            # vary vertex
            x = numpy.random.normal(vx, 4)
            y = numpy.random.normal(vy, 4)
            #z = numpy.random.normal(0, 6)
            z = vz

            E = math.sqrt(pow(mass,2) + pow(mom,2))

            outFile.write("{} 1\n".format(event_num))
            outFile.write("{} {} {} {} {} {} {} {} {} {} {} {} {} {} {}\n" \
                          .format(status, pdg, mother1, mother2, daughter1, daughter2, \
                                  p_vec[0,0], p_vec[1,0], p_vec[2,0], E, mass, x, y, z, time))

            event_num += 1

    outFile.close()

#--------------------------------------------------
if __name__ == "__main__":
    main()
