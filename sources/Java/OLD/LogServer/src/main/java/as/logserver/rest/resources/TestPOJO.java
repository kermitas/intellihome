package as.logserver.rest.resources;

import javax.xml.bind.annotation.XmlElement;
import javax.xml.bind.annotation.XmlRootElement;

// ==================================================

@XmlRootElement(name = "TestPOJO")
public class TestPOJO
{
    private String _name = "no-name";
    
    // ==============================================
    
    @XmlElement
    public String getName()
    {
        return _name;
    }
    
    // ==============================================
    
    public void setName( String name )
    {
        _name = name;
    }
    
    // ==============================================
}

// ==================================================