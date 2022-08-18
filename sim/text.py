from ROOT import TDatabasePDG,TTree,TFile
from array import array
from rootalias import *
from math import pi, cos, sin
from subprocess import call
import argparse
import os


PDG = TDatabasePDG()
EVENT_TIME_DURATION = 50.e3         # ns, 50 us per event


def convert_to_detsim_coordinates(beamsim_x, beamsim_y, beamsim_z):
    return beamsim_x + 1354.35596, beamsim_y, beamsim_z - 14648.66998


def rotate_y(x, z, degree):
    theta = degree * pi / 180.0
    x = cos(theta) * x - sin(theta) * z
    z = sin(theta) * x + cos(theta) * z
    return x, z


def save_to_txt(filename, include_noise, save_plot):
    f_beam = TFile(filename)
    particles = []
    tree = f_beam.Get('tree')
    particle_count_total = tree.GetEntries()
    particle_count = 0
    
    f = TFile("beamlinesimulation_wohoo_new.root",'recreate')
    tr = TTree("tree","tree")
    
    x_wc1 = array('f',[0])
    x_wc2 = array('f',[0])
    x_wc3 = array('f',[0])
    x_wc4 = array('f',[0])
    
    y_wc1 = array('f',[0])
    y_wc2 = array('f',[0])
    y_wc3 = array('f',[0])
    y_wc4 = array('f',[0])
    
    z_wc1 = array('f',[0])
    z_wc2 = array('f',[0])
    z_wc3 = array('f',[0])
    z_wc4 = array('f',[0])
    
    p_wc1 = array('i',[0])
    p_wc2 = array('i',[0])
    p_wc3 = array('i',[0])
    p_wc4 = array('i',[0])
    
    t_wc1 = array('f',[0])
    t_wc2 = array('f',[0])
    t_wc3 = array('f',[0])
    t_wc4 = array('f',[0])
    
    ttof_us_p=array('i',[0])
    ttof_ds_p=array('i',[0])
    ttof_us_t=array('f',[0])
    ttof_ds_t=array('f',[0])
    
    ch_t=array('f',[0])
    ch_p=array('i',[0])
    
    tr.Branch("x_wire_chamber_1", x_wc1, 'x_wire_chamber_1/f')
    tr.Branch("x_wire_chamber_2", x_wc2, 'x_wire_chamber_2/f')
    tr.Branch("x_wire_chamber_3", x_wc3, 'x_wire_chamber_3/f')
    tr.Branch("x_wire_chamber_4", x_wc4, 'x_wire_chamber_4/f')
    
    tr.Branch("y_wire_chamber_1", y_wc1, 'y_wire_chamber_1/f')
    tr.Branch("y_wire_chamber_2", y_wc2, 'y_wire_chamber_2/f')
    tr.Branch("y_wire_chamber_3", y_wc3, 'y_wire_chamber_3/f')
    tr.Branch("y_wire_chamber_4", y_wc4, 'y_wire_chamber_4/f')
    
    tr.Branch("z_wire_chamber_1", z_wc1, 'z_wire_chamber_1/f')
    tr.Branch("z_wire_chamber_2", z_wc2, 'z_wire_chamber_2/f')
    tr.Branch("z_wire_chamber_3", z_wc3, 'z_wire_chamber_3/f')
    tr.Branch("z_wire_chamber_4", z_wc4, 'z_wire_chamber_4/f')
    
    tr.Branch("t_wire_chamber_1", t_wc1, 't_wire_chamber_1/f')
    tr.Branch("t_wire_chamber_2", t_wc2, 't_wire_chamber_2/f')
    tr.Branch("t_wire_chamber_3", t_wc3, 't_wire_chamber_3/f')
    tr.Branch("t_wire_chamber_4", t_wc4, 't_wire_chamber_4/f')
    
    tr.Branch("present_wire_chamber_1", p_wc1, 'present_wire_chamber_1/i')
    tr.Branch("present_wire_chamber_2", p_wc2, 'present_wire_chamber_2/i')
    tr.Branch("present_wire_chamber_3", p_wc3, 'present_wire_chamber_3/i')
    tr.Branch("present_wire_chamber_4", p_wc4, 'present_wire_chamber_4/i')
    
    tr.Branch("t_tof_ds", ttof_ds_t, 't_tof_ds/f')
    tr.Branch("t_tof_us", ttof_us_t, 't_tof_us/f')
    tr.Branch("present_tof_us", ttof_us_p, 'present_tof_us/i')
    tr.Branch("present_tof_ds", ttof_ds_p, 'present_tof_ds/i')
    
    tr.Branch("t_cerenkov", ch_t, 't_cerenkov/f')
    tr.Branch("present_cerenkov", ch_p, 'present_cerenkov/i')

    
    for event in f_beam.Get('tree'):
        particle_count += 1
        if particle_count % 1e6 == 0:
            print('particle_count = {} / {} ({:.1f}%)'.format(particle_count, particle_count_total, particle_count / particle_count_total * 100.))

        if not include_noise and event.is_noise == 1:
            continue

        is_noise = event.is_noise
        pdg_id = int(event.pdg_id)
        px = event.px / 1000.   # GeV
        py = event.py / 1000.
        pz = event.pz / 1000.
        x, y, z = convert_to_detsim_coordinates(event.x, event.y, event.z)
        x /= 10.                # cm
        y /= 10.
        z /= 10.
        t = event.t * 1.e9      # ns
        WC1_P=event.present_wire_chamber_1
        WC2_P=event.present_wire_chamber_2
        WC3_P=event.present_wire_chamber_3
        WC4_P=event.present_wire_chamber_4
        
        WC1_T=event.t_wire_chamber_1
        WC2_T=event.t_wire_chamber_2
        WC3_T=event.t_wire_chamber_3
        WC4_T=event.t_wire_chamber_4
        
        XWC1=event.x_wire_chamber_1
        XWC2=event.x_wire_chamber_2
        XWC3=event.x_wire_chamber_3
        XWC4=event.x_wire_chamber_4
        
        YWC1=event.y_wire_chamber_1
        YWC2=event.y_wire_chamber_2
        YWC3=event.y_wire_chamber_3
        YWC4=event.y_wire_chamber_4
        
        ZWC1=event.z_wire_chamber_1
        ZWC2=event.z_wire_chamber_2
        ZWC3=event.z_wire_chamber_3
        ZWC4=event.z_wire_chamber_4
        
        TOF_US_T=event.t_tof_us
        TOF_DS_T=event.t_tof_ds
        TOF_US_P=event.present_tof_us
        TOF_DS_P=event.present_tof_ds
        
        CH_P=event.present_cerenkov
        CH_T=event.t_cerenkov
        
        mass = PDG.GetParticle(pdg_id).Mass()
        energy = (mass**2 + px**2 + py**2 + pz**2)**0.5
        particle = [is_noise,WC1_P,XWC1,YWC1,ZWC1,WC1_T,WC2_P,XWC2,YWC2,ZWC2,WC2_T,WC3_P,XWC3,YWC3,ZWC3,WC3_T,WC4_P,XWC4,YWC4,ZWC4,WC4_T,TOF_US_P,TOF_US_T,TOF_DS_P,TOF_DS_T,CH_P,CH_T,t]
        particles.append(particle)
    f_beam.Close()

    particles = sorted(particles, key=lambda x: x[-1])
    events = []
    event_end_time = 0.
    event_start_time = 0.
    event_particles = []
    for particle in particles:
        is_noise = particle[0]
        time = particle[-1]     # time
        if time > event_end_time:
            if event_particles:
                events.append(event_particles)
                event_particles = []
            if not is_noise:
                particle[-1] = 0.
                event_particles = [particle]
                event_start_time = time
                event_end_time = time + EVENT_TIME_DURATION # ns
        else:
            particle[-1] -= event_start_time
            event_particles.append(particle)

    data_dir = os.path.dirname(filename)
    filename = os.path.basename(filename)
    txt_filename = 'text_gen.{}.txt'.format(filename)
    with open ('{}/{}'.format(data_dir, txt_filename), 'w') as f_txt:
        for event in events:
            f_txt.write('0 {}\n'.format(len(event)))
            for particle in event:
                particle.pop(0)
                f_txt.write(' '.join(map(str, particle)) + '\n')
                p_wc1[0]=particle[0]
                x_wc1[0]=particle[1]
                y_wc1[0]=particle[2]
                z_wc1[0]=particle[3]
                t_wc1[0]=particle[4]
                p_wc2[0]=particle[5]
                x_wc2[0]=particle[6]
                y_wc2[0]=particle[7]
                z_wc2[0]=particle[8]
                t_wc2[0]=particle[9]
                p_wc3[0]=particle[10]
                x_wc3[0]=particle[11]
                y_wc3[0]=particle[12]
                z_wc3[0]=particle[13]
                t_wc3[0]=particle[14]
                p_wc4[0]=particle[15]
                x_wc4[0]=particle[16]
                y_wc4[0]=particle[17]
                z_wc4[0]=particle[18]
                t_wc4[0]=particle[19]
                ttof_us_p[0]=particle[20]
                ttof_us_t[0]=particle[21]
                ttof_ds_p[0]=particle[22]
                ttof_ds_t[0]=particle[23]
                ch_p[0]=particle[24]
                ch_t[0]=particle[25]
                print "particle xwc1 is",particle[1]
                tr.Fill()
    f.Write()
    f.Close()
    # call('scp {}/{} junting@novagpvm02.fnal.gov:/nova/app/users/junting/testbeam/det/'.format(data_dir, txt_filename), shell=True)

    if save_plot:
        f_det = TFile('{}/text_gen.{}.root'.format(data_dir, filename), 'RECREATE')
        multiple_particle_event_count = 0
        h_count = TH1D('h_count', 'h_count', 100, -0.5, 99.5)
        h_timing = TH1D('h_timing', 'h_timing', 5000, 0., 50.e3) # ns
        for i, event in enumerate(events):
            h_count.Fill(len(event))
            if len(event) > 1:
                multiple_particle_event_count += 1
                #print('i = {}'.format(i))
                #print('len(event) = {}'.format(len(event)))
            for particle in event:
                h_timing.Fill(particle[-1])
        print('len(events) = {}'.format(len(events)))
        print('multiple_particle_event_count = {}'.format(multiple_particle_event_count))
        h_count.Write('h_particle_count_per_event')
        h_timing.Write('h_timing')
        f_det.Close()


if __name__ == '__main__':
    parser = argparse.ArgumentParser()
    parser.add_argument('-f', '--filename', type=str, help='input filename', required=True)
    parser.add_argument('-s', '--save_plot', help='save particle count per event', action='store_true')
    parser.add_argument('-n', '--include_noise', help='include noise', action='store_true')

    args = parser.parse_args()
    print('args.filename = {}'.format(args.filename))
    print('args.save_plot = {}'.format(args.save_plot))
    print('args.include_noise = {}'.format(args.include_noise))
    save_to_txt(args.filename, args.include_noise, args.save_plot)
