
try: import tempfile, wave, subprocess, os, signal, struct
except: 
    print("E: sound4python is unable to import a combination of %s"%
            ("tempfile, wave, subprocess, os, signal, struct"))

FNULL = open(os.devnull,'w')
def launchWithoutConsole(args,output=False):
    """Launches args windowless and waits until finished"""
    startupinfo = None
    if( 'STARTUPINFO' in dir(subprocess) ):
        startupinfo = subprocess.STARTUPINFO()
        startupinfo.dwFlags |= subprocess.STARTF_USESHOWWINDOW
    if( output ):
        return subprocess.Popen(args, stdin=subprocess.PIPE,
                stdout=subprocess.PIPE,startupinfo=startupinfo, )
    else:
        return subprocess.Popen(args, stdin=subprocess.PIPE,
                stdout=FNULL ,stderr=FNULL, startupinfo=startupinfo)
 
# sound4python
def sound(itr,samprate=16000,autoscale=True,output=False):
    try: import numpy as np; foundNumpy=True;
    except: 
        foundNumpy=False;

    #for now, assume 1-D iterable
    mult = 1
    if( autoscale ):
        mult = 32767.0 / max(itr)
        #mult = 128.0 / max(itr)

    #create file in memory
    #with tempfile.SpooledTemporaryFile() as memFile:
    memFile = tempfile.SpooledTemporaryFile()

    #create wave write objection pointing to memFile
    waveWrite = wave.open(memFile,'wb')
    waveWrite.setsampwidth(2)        # int16 default
    waveWrite.setnchannels(1)        # mono  default
    waveWrite.setframerate(samprate) # 8kHz  default
    
    wroteFrames=False
    #Let's try to create sound from NumPy vector
    if( foundNumpy ):
        if( type(itr)==np.array ):
            if( itr.ndim == 1 or itr.shape.count(1) == itr.ndim - 1 ):
                waveWrite.writeframes( (mult*itr.flatten()).astype(np.int16).tostring() )
                wroteFrames=True
        else: #we have np, but the iterable isn't a vector
            waveWrite.writeframes( (mult*np.array(itr)).astype(np.int16).tostring() )
            wroteFrames=True
    if( not wroteFrames and not foundNumpy ):
        #python w/o np doesn't have "short"/"int16", "@h" is "native,aligned short"
        # BAD : waveWrite.writeframes( struct.pack(len(itr)*"@h",[int(mult*itm) for itm in itr]) )
        writeValues = []
        for itm in itr:
            packed_value = struct.pack('h', int(mult*itm))
            waveWrite.writeframes(packed_value)

        wroteFrames=True
        
    if( not wroteFrames ):
        print("E: Unable to create sound.  Only 1D numpy arrays and numerical lists are supported.")
        waveWrite.close()
        return None

    #configure the file object, memFile, as if it has just been opened for reading
    memFile.seek(0)

    try:
        # getting here means wroteFrames == True
        #print("\nAttempting to play a mono audio stream of length")
        #print("  %.2f seconds (%.3f thousand samples at sample rate of %.3f kHz)"%
        #        ( 1.0*len(itr)/samprate , len(itr)/1000. , int(samprate)/1000.) )
        p=launchWithoutConsole(['sox','-','-d'])
    except: 
        print("E: Unable to launch sox.")
        print("E: Please ensure that sox is installed and on the path.")
        print("E: Try 'sox -h' to test sox installation.")
        waveWrite.close()
        return None

    try: 
        p.communicate(memFile.read())
        p.wait()
    except: 
        print("E: Unable to send in-memory wave file to stdin of sox subprocess.")
        waveWrite.close()
        return None
    #os.kill(p.pid,signal.CTRL_C_EVENT)
#end def sound(itr,samprate=8000,autoscale=True)
        






