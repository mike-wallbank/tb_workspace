import math
import numpy

outfile = open('evts.txt','w')

#--------------------------------------------------
def write_event(evtnum, px, py, pz, E, vertx, verty):
    outfile.write("%d 1\n" %(evtnum))
    outfile.write("1 2212 0 0 0 0 %f %f %f %f 0.938 %f %f -445 50340\n" % (px, py, pz, E, vertx, verty))

#--------------------------------------------------
def main():
    smear = True
    with open('stats-for-sim.txt','r') as infile:
        lines = infile.readlines()

        evtnum=1
        for line in lines:
            if line.startswith("#"):
                continue
            wcmom = float(line.split()[0])
            vertx = float(line.split()[2])
            verty = float(line.split()[3])
            dirx  = float(line.split()[4])
            diry  = float(line.split()[5])
            dirz  = float(line.split()[6])

            # adjust direction ± 10 mrad
            # + in gdml corresponds to - here
            dirx = dirx + 0.01

            vertx = vertx - 445*dirx
            verty = verty - 445*diry            
            #if wcmom<980 or wcmom>990:
                #continue
        
            mom = wcmom/1e3
            px  = mom*dirx
            py  = mom*diry
            pz  = mom*dirz
            E   = math.sqrt(pow(0.938,2) + pow(mom,2))
 
            #if mom<.980 or mom>.990:
            #    continue

            write_event(evtnum, px, py, pz, E, vertx, verty)
            evtnum+=1

            # theta = azimuthal angle in x-y plane, phi = polar angle from z-axis
            theta = math.atan2(diry,dirx)
            phi = math.acos(dirz)
            
            if (smear):
                for i in range(0,99):
                    # 5% spread in momentum
                    #mom = numpy.random.normal(wcmom/1e3,wcmom/1e3*0.05)
                    #if mom<.980 or mom>.990:
                    #    continue
                    # vary theta and phi by 4 mrad
                    #theta2 = numpy.random.normal(theta,0.004)
                    #phi2 = numpy.random.normal(phi,0.004)
                    #px = mom*math.sin(phi2)*math.cos(theta2)
                    #py = mom*math.sin(phi2)*math.sin(theta2)
                    #pz = mom*math.cos(phi2)
                    #px = mom*dirx
                    #py = mom*diry
                    #pz = mom*dirz
                    # vary x and y by cell width

                    #x = numpy.random.normal(vertx,4)
                    #y = numpy.random.normal(verty,4)
                    x = vertx
                    y = verty
                    #E  = math.sqrt(pow(0.938,2) + pow(mom,2))
                    
                    write_event(evtnum, px, py, pz, E, x, y)
                    evtnum+=1

    outfile.close()

#--------------------------------------------------
if __name__ == "__main__":
    # execute only if run as a script
    main()
