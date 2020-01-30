import polyscope_bindings as psb

### Basic setup and teardown 

def init():
    """Initialize Polyscope"""
    psb.init()


def show(forFrames=None):
    """Show the Polyscope GUI (blocks until UI is exited)"""
    if forFrames is None:
        psb.show()
    else:
        psb.show(forFrames)




### Structure management

def remove_all_structures():
    """Remove all structures from Polyscope"""
    psb.remove_all_structures()


### Small options
def set_errors_throw_exceptions(val):
    psb.set_errors_throw_exceptions(val)
