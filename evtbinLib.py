#$Id: evtbinLib.py,v 1.4 2015/03/05 19:58:35 echarles Exp $
def generate(env, **kw):
    if not kw.get('depsOnly',0):
        env.Tool('addLibrary', library = ['evtbin'])
    env.Tool('astroLib')
    env.Tool('st_appLib')
    env.Tool('st_facilitiesLib')
    env.Tool('st_streamLib')
    env.Tool('tipLib')
    # EAC, add dependence on HEALPix external
    env.Tool('addLibrary', library=env['healpixlibs'])

def exists(env):
    return 1
