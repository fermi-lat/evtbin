# -*- python -*-
# $Id: SConscript,v 1.15 2009/07/15 19:14:01 jrb Exp $
# Authors: James Peachey <James.Peachey-1@nasa.gov>
# Version: evtbin-02-03-01

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

progEnv.Tool('registerTargets', package = 'evtbin', staticLibraryCxts = [[evtbinLib, libEnv]],
             binaryCxts = [[gtbinBin, progEnv], [gtbindefBin, progEnv]],
             testAppCxts = [[test_evtbinBin, progEnv]], includes = listFiles(['evtbin/*.h']),
             pfiles = listFiles(['pfiles/*.par']), data = listFiles(['data/*'], recursive = True))
