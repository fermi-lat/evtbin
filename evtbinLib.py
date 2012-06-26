#$Id: evtbinLib.py,v 1.2 2008/02/26 03:10:49 glastrm Exp $
def generate(env, **kw):
    if not kw.get('depsOnly',0):
        env.Tool('addLibrary', library = ['evtbin'])
    env.Tool('astroLib')
    env.Tool('st_appLib')
    env.Tool('st_facilitiesLib')
    env.Tool('st_streamLib')
    env.Tool('tipLib')
    env.Tool('healpixLib')

def exists(env):
    return 1
