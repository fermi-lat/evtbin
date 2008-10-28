# -*- python -*-
# $Id: SConscript,v 1.10 2008/10/28 15:30:37 glastrm Exp $
# Authors: James Peachey <James.Peachey-1@nasa.gov>
# Version: evtbin-02-02-01

Import('baseEnv')
Import('listFiles')
progEnv = baseEnv.Clone()
libEnv = baseEnv.Clone()

libEnv.Tool('evtbinLib', depsOnly = 1)
evtbinLib = libEnv.StaticLibrary('evtbin', listFiles(['src/*.cxx']))

progEnv.Tool('evtbinLib')
gtbinBin = progEnv.Program('gtbin', listFiles(['src/gtbin/*.cxx']))
gtbindefBin = progEnv.Program('gtbindef', listFiles(['src/gtbindef/*.cxx']))
test_evtbinBin = progEnv.Program('test_evtbin', listFiles(['src/test/*.cxx']))

progEnv.Tool('registerObjects', package = 'evtbin', libraries = [evtbinLib], binaries = [gtbinBin, gtbindefBin], testApps = [test_evtbinBin], includes = listFiles(['evtbin/*.h']),
             pfiles = listFiles(['pfiles/*.par']), data = listFiles(['data/*'], recursive = True))
