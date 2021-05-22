enum State { tx, rx, error };
enum Band { 160m, 80m, 60m, 40m, 30m, 20m, 17m, 15m, 12m, 10m };

class BandMapping {
    Band band;
    bool LPFSwitches[3];
}