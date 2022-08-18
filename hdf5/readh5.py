import h5py
filename = "testbeam_r00101450_s09_beamline_R21-07-27-testbeam-production.h5caf.h5"

with h5py.File(filename, "r") as f:
    # List all groups
    print("Keys: %s" % f.keys())
    a_group_key = list(f.keys())[0]

    # Get the data
    data = list(f[a_group_key])
