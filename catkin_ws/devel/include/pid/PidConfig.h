//#line 2 "/opt/ros/noetic/share/dynamic_reconfigure/cmake/../templates/ConfigType.h.template"
// *********************************************************
//
// File autogenerated for the pid package
// by the dynamic_reconfigure package.
// Please do not edit.
//
// ********************************************************/

#ifndef __pid__PIDCONFIG_H__
#define __pid__PIDCONFIG_H__

#if __cplusplus >= 201103L
#define DYNAMIC_RECONFIGURE_FINAL final
#else
#define DYNAMIC_RECONFIGURE_FINAL
#endif

#include <dynamic_reconfigure/config_tools.h>
#include <limits>
#include <ros/node_handle.h>
#include <dynamic_reconfigure/ConfigDescription.h>
#include <dynamic_reconfigure/ParamDescription.h>
#include <dynamic_reconfigure/Group.h>
#include <dynamic_reconfigure/config_init_mutex.h>
#include <boost/any.hpp>

namespace pid
{
  class PidConfigStatics;

  class PidConfig
  {
  public:
    class AbstractParamDescription : public dynamic_reconfigure::ParamDescription
    {
    public:
      AbstractParamDescription(std::string n, std::string t, uint32_t l,
          std::string d, std::string e)
      {
        name = n;
        type = t;
        level = l;
        description = d;
        edit_method = e;
      }
      virtual ~AbstractParamDescription() = default;

      virtual void clamp(PidConfig &config, const PidConfig &max, const PidConfig &min) const = 0;
      virtual void calcLevel(uint32_t &level, const PidConfig &config1, const PidConfig &config2) const = 0;
      virtual void fromServer(const ros::NodeHandle &nh, PidConfig &config) const = 0;
      virtual void toServer(const ros::NodeHandle &nh, const PidConfig &config) const = 0;
      virtual bool fromMessage(const dynamic_reconfigure::Config &msg, PidConfig &config) const = 0;
      virtual void toMessage(dynamic_reconfigure::Config &msg, const PidConfig &config) const = 0;
      virtual void getValue(const PidConfig &config, boost::any &val) const = 0;
    };

    typedef boost::shared_ptr<AbstractParamDescription> AbstractParamDescriptionPtr;
    typedef boost::shared_ptr<const AbstractParamDescription> AbstractParamDescriptionConstPtr;

    // Final keyword added to class because it has virtual methods and inherits
    // from a class with a non-virtual destructor.
    template <class T>
    class ParamDescription DYNAMIC_RECONFIGURE_FINAL : public AbstractParamDescription
    {
    public:
      ParamDescription(std::string a_name, std::string a_type, uint32_t a_level,
          std::string a_description, std::string a_edit_method, T PidConfig::* a_f) :
        AbstractParamDescription(a_name, a_type, a_level, a_description, a_edit_method),
        field(a_f)
      {}

      T PidConfig::* field;

      virtual void clamp(PidConfig &config, const PidConfig &max, const PidConfig &min) const override
      {
        if (config.*field > max.*field)
          config.*field = max.*field;

        if (config.*field < min.*field)
          config.*field = min.*field;
      }

      virtual void calcLevel(uint32_t &comb_level, const PidConfig &config1, const PidConfig &config2) const override
      {
        if (config1.*field != config2.*field)
          comb_level |= level;
      }

      virtual void fromServer(const ros::NodeHandle &nh, PidConfig &config) const override
      {
        nh.getParam(name, config.*field);
      }

      virtual void toServer(const ros::NodeHandle &nh, const PidConfig &config) const override
      {
        nh.setParam(name, config.*field);
      }

      virtual bool fromMessage(const dynamic_reconfigure::Config &msg, PidConfig &config) const override
      {
        return dynamic_reconfigure::ConfigTools::getParameter(msg, name, config.*field);
      }

      virtual void toMessage(dynamic_reconfigure::Config &msg, const PidConfig &config) const override
      {
        dynamic_reconfigure::ConfigTools::appendParameter(msg, name, config.*field);
      }

      virtual void getValue(const PidConfig &config, boost::any &val) const override
      {
        val = config.*field;
      }
    };

    class AbstractGroupDescription : public dynamic_reconfigure::Group
    {
      public:
      AbstractGroupDescription(std::string n, std::string t, int p, int i, bool s)
      {
        name = n;
        type = t;
        parent = p;
        state = s;
        id = i;
      }

      virtual ~AbstractGroupDescription() = default;

      std::vector<AbstractParamDescriptionConstPtr> abstract_parameters;
      bool state;

      virtual void toMessage(dynamic_reconfigure::Config &msg, const boost::any &config) const = 0;
      virtual bool fromMessage(const dynamic_reconfigure::Config &msg, boost::any &config) const =0;
      virtual void updateParams(boost::any &cfg, PidConfig &top) const= 0;
      virtual void setInitialState(boost::any &cfg) const = 0;


      void convertParams()
      {
        for(std::vector<AbstractParamDescriptionConstPtr>::const_iterator i = abstract_parameters.begin(); i != abstract_parameters.end(); ++i)
        {
          parameters.push_back(dynamic_reconfigure::ParamDescription(**i));
        }
      }
    };

    typedef boost::shared_ptr<AbstractGroupDescription> AbstractGroupDescriptionPtr;
    typedef boost::shared_ptr<const AbstractGroupDescription> AbstractGroupDescriptionConstPtr;

    // Final keyword added to class because it has virtual methods and inherits
    // from a class with a non-virtual destructor.
    template<class T, class PT>
    class GroupDescription DYNAMIC_RECONFIGURE_FINAL : public AbstractGroupDescription
    {
    public:
      GroupDescription(std::string a_name, std::string a_type, int a_parent, int a_id, bool a_s, T PT::* a_f) : AbstractGroupDescription(a_name, a_type, a_parent, a_id, a_s), field(a_f)
      {
      }

      GroupDescription(const GroupDescription<T, PT>& g): AbstractGroupDescription(g.name, g.type, g.parent, g.id, g.state), field(g.field), groups(g.groups)
      {
        parameters = g.parameters;
        abstract_parameters = g.abstract_parameters;
      }

      virtual bool fromMessage(const dynamic_reconfigure::Config &msg, boost::any &cfg) const override
      {
        PT* config = boost::any_cast<PT*>(cfg);
        if(!dynamic_reconfigure::ConfigTools::getGroupState(msg, name, (*config).*field))
          return false;

        for(std::vector<AbstractGroupDescriptionConstPtr>::const_iterator i = groups.begin(); i != groups.end(); ++i)
        {
          boost::any n = &((*config).*field);
          if(!(*i)->fromMessage(msg, n))
            return false;
        }

        return true;
      }

      virtual void setInitialState(boost::any &cfg) const override
      {
        PT* config = boost::any_cast<PT*>(cfg);
        T* group = &((*config).*field);
        group->state = state;

        for(std::vector<AbstractGroupDescriptionConstPtr>::const_iterator i = groups.begin(); i != groups.end(); ++i)
        {
          boost::any n = boost::any(&((*config).*field));
          (*i)->setInitialState(n);
        }

      }

      virtual void updateParams(boost::any &cfg, PidConfig &top) const override
      {
        PT* config = boost::any_cast<PT*>(cfg);

        T* f = &((*config).*field);
        f->setParams(top, abstract_parameters);

        for(std::vector<AbstractGroupDescriptionConstPtr>::const_iterator i = groups.begin(); i != groups.end(); ++i)
        {
          boost::any n = &((*config).*field);
          (*i)->updateParams(n, top);
        }
      }

      virtual void toMessage(dynamic_reconfigure::Config &msg, const boost::any &cfg) const override
      {
        const PT config = boost::any_cast<PT>(cfg);
        dynamic_reconfigure::ConfigTools::appendGroup<T>(msg, name, id, parent, config.*field);

        for(std::vector<AbstractGroupDescriptionConstPtr>::const_iterator i = groups.begin(); i != groups.end(); ++i)
        {
          (*i)->toMessage(msg, config.*field);
        }
      }

      T PT::* field;
      std::vector<PidConfig::AbstractGroupDescriptionConstPtr> groups;
    };

class DEFAULT
{
  public:
    DEFAULT()
    {
      state = true;
      name = "Default";
    }

    void setParams(PidConfig &config, const std::vector<AbstractParamDescriptionConstPtr> params)
    {
      for (std::vector<AbstractParamDescriptionConstPtr>::const_iterator _i = params.begin(); _i != params.end(); ++_i)
      {
        boost::any val;
        (*_i)->getValue(config, val);

        if("Kp_scale"==(*_i)->name){Kp_scale = boost::any_cast<double>(val);}
        if("Kp"==(*_i)->name){Kp = boost::any_cast<double>(val);}
        if("Ki_scale"==(*_i)->name){Ki_scale = boost::any_cast<double>(val);}
        if("Ki"==(*_i)->name){Ki = boost::any_cast<double>(val);}
        if("Kd_scale"==(*_i)->name){Kd_scale = boost::any_cast<double>(val);}
        if("Kd"==(*_i)->name){Kd = boost::any_cast<double>(val);}
      }
    }

    double Kp_scale;
double Kp;
double Ki_scale;
double Ki;
double Kd_scale;
double Kd;

    bool state;
    std::string name;

    
}groups;



//#line 291 "/opt/ros/noetic/lib/python3/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      double Kp_scale;
//#line 291 "/opt/ros/noetic/lib/python3/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      double Kp;
//#line 291 "/opt/ros/noetic/lib/python3/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      double Ki_scale;
//#line 291 "/opt/ros/noetic/lib/python3/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      double Ki;
//#line 291 "/opt/ros/noetic/lib/python3/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      double Kd_scale;
//#line 291 "/opt/ros/noetic/lib/python3/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      double Kd;
//#line 231 "/opt/ros/noetic/share/dynamic_reconfigure/cmake/../templates/ConfigType.h.template"

    bool __fromMessage__(dynamic_reconfigure::Config &msg)
    {
      const std::vector<AbstractParamDescriptionConstPtr> &__param_descriptions__ = __getParamDescriptions__();
      const std::vector<AbstractGroupDescriptionConstPtr> &__group_descriptions__ = __getGroupDescriptions__();

      int count = 0;
      for (std::vector<AbstractParamDescriptionConstPtr>::const_iterator i = __param_descriptions__.begin(); i != __param_descriptions__.end(); ++i)
        if ((*i)->fromMessage(msg, *this))
          count++;

      for (std::vector<AbstractGroupDescriptionConstPtr>::const_iterator i = __group_descriptions__.begin(); i != __group_descriptions__.end(); i ++)
      {
        if ((*i)->id == 0)
        {
          boost::any n = boost::any(this);
          (*i)->updateParams(n, *this);
          (*i)->fromMessage(msg, n);
        }
      }

      if (count != dynamic_reconfigure::ConfigTools::size(msg))
      {
        ROS_ERROR("PidConfig::__fromMessage__ called with an unexpected parameter.");
        ROS_ERROR("Booleans:");
        for (unsigned int i = 0; i < msg.bools.size(); i++)
          ROS_ERROR("  %s", msg.bools[i].name.c_str());
        ROS_ERROR("Integers:");
        for (unsigned int i = 0; i < msg.ints.size(); i++)
          ROS_ERROR("  %s", msg.ints[i].name.c_str());
        ROS_ERROR("Doubles:");
        for (unsigned int i = 0; i < msg.doubles.size(); i++)
          ROS_ERROR("  %s", msg.doubles[i].name.c_str());
        ROS_ERROR("Strings:");
        for (unsigned int i = 0; i < msg.strs.size(); i++)
          ROS_ERROR("  %s", msg.strs[i].name.c_str());
        // @todo Check that there are no duplicates. Make this error more
        // explicit.
        return false;
      }
      return true;
    }

    // This version of __toMessage__ is used during initialization of
    // statics when __getParamDescriptions__ can't be called yet.
    void __toMessage__(dynamic_reconfigure::Config &msg, const std::vector<AbstractParamDescriptionConstPtr> &__param_descriptions__, const std::vector<AbstractGroupDescriptionConstPtr> &__group_descriptions__) const
    {
      dynamic_reconfigure::ConfigTools::clear(msg);
      for (std::vector<AbstractParamDescriptionConstPtr>::const_iterator i = __param_descriptions__.begin(); i != __param_descriptions__.end(); ++i)
        (*i)->toMessage(msg, *this);

      for (std::vector<AbstractGroupDescriptionConstPtr>::const_iterator i = __group_descriptions__.begin(); i != __group_descriptions__.end(); ++i)
      {
        if((*i)->id == 0)
        {
          (*i)->toMessage(msg, *this);
        }
      }
    }

    void __toMessage__(dynamic_reconfigure::Config &msg) const
    {
      const std::vector<AbstractParamDescriptionConstPtr> &__param_descriptions__ = __getParamDescriptions__();
      const std::vector<AbstractGroupDescriptionConstPtr> &__group_descriptions__ = __getGroupDescriptions__();
      __toMessage__(msg, __param_descriptions__, __group_descriptions__);
    }

    void __toServer__(const ros::NodeHandle &nh) const
    {
      const std::vector<AbstractParamDescriptionConstPtr> &__param_descriptions__ = __getParamDescriptions__();
      for (std::vector<AbstractParamDescriptionConstPtr>::const_iterator i = __param_descriptions__.begin(); i != __param_descriptions__.end(); ++i)
        (*i)->toServer(nh, *this);
    }

    void __fromServer__(const ros::NodeHandle &nh)
    {
      static bool setup=false;

      const std::vector<AbstractParamDescriptionConstPtr> &__param_descriptions__ = __getParamDescriptions__();
      for (std::vector<AbstractParamDescriptionConstPtr>::const_iterator i = __param_descriptions__.begin(); i != __param_descriptions__.end(); ++i)
        (*i)->fromServer(nh, *this);

      const std::vector<AbstractGroupDescriptionConstPtr> &__group_descriptions__ = __getGroupDescriptions__();
      for (std::vector<AbstractGroupDescriptionConstPtr>::const_iterator i = __group_descriptions__.begin(); i != __group_descriptions__.end(); i++){
        if (!setup && (*i)->id == 0) {
          setup = true;
          boost::any n = boost::any(this);
          (*i)->setInitialState(n);
        }
      }
    }

    void __clamp__()
    {
      const std::vector<AbstractParamDescriptionConstPtr> &__param_descriptions__ = __getParamDescriptions__();
      const PidConfig &__max__ = __getMax__();
      const PidConfig &__min__ = __getMin__();
      for (std::vector<AbstractParamDescriptionConstPtr>::const_iterator i = __param_descriptions__.begin(); i != __param_descriptions__.end(); ++i)
        (*i)->clamp(*this, __max__, __min__);
    }

    uint32_t __level__(const PidConfig &config) const
    {
      const std::vector<AbstractParamDescriptionConstPtr> &__param_descriptions__ = __getParamDescriptions__();
      uint32_t level = 0;
      for (std::vector<AbstractParamDescriptionConstPtr>::const_iterator i = __param_descriptions__.begin(); i != __param_descriptions__.end(); ++i)
        (*i)->calcLevel(level, config, *this);
      return level;
    }

    static const dynamic_reconfigure::ConfigDescription &__getDescriptionMessage__();
    static const PidConfig &__getDefault__();
    static const PidConfig &__getMax__();
    static const PidConfig &__getMin__();
    static const std::vector<AbstractParamDescriptionConstPtr> &__getParamDescriptions__();
    static const std::vector<AbstractGroupDescriptionConstPtr> &__getGroupDescriptions__();

  private:
    static const PidConfigStatics *__get_statics__();
  };

  template <> // Max and min are ignored for strings.
  inline void PidConfig::ParamDescription<std::string>::clamp(PidConfig &config, const PidConfig &max, const PidConfig &min) const
  {
    (void) config;
    (void) min;
    (void) max;
    return;
  }

  class PidConfigStatics
  {
    friend class PidConfig;

    PidConfigStatics()
    {
PidConfig::GroupDescription<PidConfig::DEFAULT, PidConfig> Default("Default", "", 0, 0, true, &PidConfig::groups);
//#line 291 "/opt/ros/noetic/lib/python3/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      __min__.Kp_scale = 0.1;
//#line 291 "/opt/ros/noetic/lib/python3/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      __max__.Kp_scale = 100.0;
//#line 291 "/opt/ros/noetic/lib/python3/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      __default__.Kp_scale = 10.0;
//#line 291 "/opt/ros/noetic/lib/python3/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      Default.abstract_parameters.push_back(PidConfig::AbstractParamDescriptionConstPtr(new PidConfig::ParamDescription<double>("Kp_scale", "double", 0, "Kp scale", "{'enum': [{'name': 'scale_tenth', 'type': 'double', 'value': 0.1, 'srcline': 7, 'srcfile': '/home/alok/catkin_ws/src/pid/cfg/Pid.cfg', 'description': 'Scale by 0.1', 'ctype': 'double', 'cconsttype': 'const double'}, {'name': 'scale_unity', 'type': 'double', 'value': 1.0, 'srcline': 8, 'srcfile': '/home/alok/catkin_ws/src/pid/cfg/Pid.cfg', 'description': 'No scaling', 'ctype': 'double', 'cconsttype': 'const double'}, {'name': 'scale_ten', 'type': 'double', 'value': 10.0, 'srcline': 9, 'srcfile': '/home/alok/catkin_ws/src/pid/cfg/Pid.cfg', 'description': 'Scale by 10', 'ctype': 'double', 'cconsttype': 'const double'}, {'name': 'scale_hundred', 'type': 'double', 'value': 100.0, 'srcline': 10, 'srcfile': '/home/alok/catkin_ws/src/pid/cfg/Pid.cfg', 'description': 'Scale by 100', 'ctype': 'double', 'cconsttype': 'const double'}], 'enum_description': 'Scale factor for K setting'}", &PidConfig::Kp_scale)));
//#line 291 "/opt/ros/noetic/lib/python3/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      __param_descriptions__.push_back(PidConfig::AbstractParamDescriptionConstPtr(new PidConfig::ParamDescription<double>("Kp_scale", "double", 0, "Kp scale", "{'enum': [{'name': 'scale_tenth', 'type': 'double', 'value': 0.1, 'srcline': 7, 'srcfile': '/home/alok/catkin_ws/src/pid/cfg/Pid.cfg', 'description': 'Scale by 0.1', 'ctype': 'double', 'cconsttype': 'const double'}, {'name': 'scale_unity', 'type': 'double', 'value': 1.0, 'srcline': 8, 'srcfile': '/home/alok/catkin_ws/src/pid/cfg/Pid.cfg', 'description': 'No scaling', 'ctype': 'double', 'cconsttype': 'const double'}, {'name': 'scale_ten', 'type': 'double', 'value': 10.0, 'srcline': 9, 'srcfile': '/home/alok/catkin_ws/src/pid/cfg/Pid.cfg', 'description': 'Scale by 10', 'ctype': 'double', 'cconsttype': 'const double'}, {'name': 'scale_hundred', 'type': 'double', 'value': 100.0, 'srcline': 10, 'srcfile': '/home/alok/catkin_ws/src/pid/cfg/Pid.cfg', 'description': 'Scale by 100', 'ctype': 'double', 'cconsttype': 'const double'}], 'enum_description': 'Scale factor for K setting'}", &PidConfig::Kp_scale)));
//#line 291 "/opt/ros/noetic/lib/python3/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      __min__.Kp = -1.0;
//#line 291 "/opt/ros/noetic/lib/python3/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      __max__.Kp = 1.0;
//#line 291 "/opt/ros/noetic/lib/python3/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      __default__.Kp = 0.1;
//#line 291 "/opt/ros/noetic/lib/python3/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      Default.abstract_parameters.push_back(PidConfig::AbstractParamDescriptionConstPtr(new PidConfig::ParamDescription<double>("Kp", "double", 0, "Kp", "", &PidConfig::Kp)));
//#line 291 "/opt/ros/noetic/lib/python3/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      __param_descriptions__.push_back(PidConfig::AbstractParamDescriptionConstPtr(new PidConfig::ParamDescription<double>("Kp", "double", 0, "Kp", "", &PidConfig::Kp)));
//#line 291 "/opt/ros/noetic/lib/python3/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      __min__.Ki_scale = 0.1;
//#line 291 "/opt/ros/noetic/lib/python3/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      __max__.Ki_scale = 100.0;
//#line 291 "/opt/ros/noetic/lib/python3/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      __default__.Ki_scale = 10.0;
//#line 291 "/opt/ros/noetic/lib/python3/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      Default.abstract_parameters.push_back(PidConfig::AbstractParamDescriptionConstPtr(new PidConfig::ParamDescription<double>("Ki_scale", "double", 0, "Ki scale", "{'enum': [{'name': 'scale_tenth', 'type': 'double', 'value': 0.1, 'srcline': 7, 'srcfile': '/home/alok/catkin_ws/src/pid/cfg/Pid.cfg', 'description': 'Scale by 0.1', 'ctype': 'double', 'cconsttype': 'const double'}, {'name': 'scale_unity', 'type': 'double', 'value': 1.0, 'srcline': 8, 'srcfile': '/home/alok/catkin_ws/src/pid/cfg/Pid.cfg', 'description': 'No scaling', 'ctype': 'double', 'cconsttype': 'const double'}, {'name': 'scale_ten', 'type': 'double', 'value': 10.0, 'srcline': 9, 'srcfile': '/home/alok/catkin_ws/src/pid/cfg/Pid.cfg', 'description': 'Scale by 10', 'ctype': 'double', 'cconsttype': 'const double'}, {'name': 'scale_hundred', 'type': 'double', 'value': 100.0, 'srcline': 10, 'srcfile': '/home/alok/catkin_ws/src/pid/cfg/Pid.cfg', 'description': 'Scale by 100', 'ctype': 'double', 'cconsttype': 'const double'}], 'enum_description': 'Scale factor for K setting'}", &PidConfig::Ki_scale)));
//#line 291 "/opt/ros/noetic/lib/python3/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      __param_descriptions__.push_back(PidConfig::AbstractParamDescriptionConstPtr(new PidConfig::ParamDescription<double>("Ki_scale", "double", 0, "Ki scale", "{'enum': [{'name': 'scale_tenth', 'type': 'double', 'value': 0.1, 'srcline': 7, 'srcfile': '/home/alok/catkin_ws/src/pid/cfg/Pid.cfg', 'description': 'Scale by 0.1', 'ctype': 'double', 'cconsttype': 'const double'}, {'name': 'scale_unity', 'type': 'double', 'value': 1.0, 'srcline': 8, 'srcfile': '/home/alok/catkin_ws/src/pid/cfg/Pid.cfg', 'description': 'No scaling', 'ctype': 'double', 'cconsttype': 'const double'}, {'name': 'scale_ten', 'type': 'double', 'value': 10.0, 'srcline': 9, 'srcfile': '/home/alok/catkin_ws/src/pid/cfg/Pid.cfg', 'description': 'Scale by 10', 'ctype': 'double', 'cconsttype': 'const double'}, {'name': 'scale_hundred', 'type': 'double', 'value': 100.0, 'srcline': 10, 'srcfile': '/home/alok/catkin_ws/src/pid/cfg/Pid.cfg', 'description': 'Scale by 100', 'ctype': 'double', 'cconsttype': 'const double'}], 'enum_description': 'Scale factor for K setting'}", &PidConfig::Ki_scale)));
//#line 291 "/opt/ros/noetic/lib/python3/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      __min__.Ki = -1.0;
//#line 291 "/opt/ros/noetic/lib/python3/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      __max__.Ki = 1.0;
//#line 291 "/opt/ros/noetic/lib/python3/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      __default__.Ki = 0.1;
//#line 291 "/opt/ros/noetic/lib/python3/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      Default.abstract_parameters.push_back(PidConfig::AbstractParamDescriptionConstPtr(new PidConfig::ParamDescription<double>("Ki", "double", 0, "Ki", "", &PidConfig::Ki)));
//#line 291 "/opt/ros/noetic/lib/python3/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      __param_descriptions__.push_back(PidConfig::AbstractParamDescriptionConstPtr(new PidConfig::ParamDescription<double>("Ki", "double", 0, "Ki", "", &PidConfig::Ki)));
//#line 291 "/opt/ros/noetic/lib/python3/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      __min__.Kd_scale = 0.1;
//#line 291 "/opt/ros/noetic/lib/python3/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      __max__.Kd_scale = 100.0;
//#line 291 "/opt/ros/noetic/lib/python3/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      __default__.Kd_scale = 10.0;
//#line 291 "/opt/ros/noetic/lib/python3/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      Default.abstract_parameters.push_back(PidConfig::AbstractParamDescriptionConstPtr(new PidConfig::ParamDescription<double>("Kd_scale", "double", 0, "Kd scale", "{'enum': [{'name': 'scale_tenth', 'type': 'double', 'value': 0.1, 'srcline': 7, 'srcfile': '/home/alok/catkin_ws/src/pid/cfg/Pid.cfg', 'description': 'Scale by 0.1', 'ctype': 'double', 'cconsttype': 'const double'}, {'name': 'scale_unity', 'type': 'double', 'value': 1.0, 'srcline': 8, 'srcfile': '/home/alok/catkin_ws/src/pid/cfg/Pid.cfg', 'description': 'No scaling', 'ctype': 'double', 'cconsttype': 'const double'}, {'name': 'scale_ten', 'type': 'double', 'value': 10.0, 'srcline': 9, 'srcfile': '/home/alok/catkin_ws/src/pid/cfg/Pid.cfg', 'description': 'Scale by 10', 'ctype': 'double', 'cconsttype': 'const double'}, {'name': 'scale_hundred', 'type': 'double', 'value': 100.0, 'srcline': 10, 'srcfile': '/home/alok/catkin_ws/src/pid/cfg/Pid.cfg', 'description': 'Scale by 100', 'ctype': 'double', 'cconsttype': 'const double'}], 'enum_description': 'Scale factor for K setting'}", &PidConfig::Kd_scale)));
//#line 291 "/opt/ros/noetic/lib/python3/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      __param_descriptions__.push_back(PidConfig::AbstractParamDescriptionConstPtr(new PidConfig::ParamDescription<double>("Kd_scale", "double", 0, "Kd scale", "{'enum': [{'name': 'scale_tenth', 'type': 'double', 'value': 0.1, 'srcline': 7, 'srcfile': '/home/alok/catkin_ws/src/pid/cfg/Pid.cfg', 'description': 'Scale by 0.1', 'ctype': 'double', 'cconsttype': 'const double'}, {'name': 'scale_unity', 'type': 'double', 'value': 1.0, 'srcline': 8, 'srcfile': '/home/alok/catkin_ws/src/pid/cfg/Pid.cfg', 'description': 'No scaling', 'ctype': 'double', 'cconsttype': 'const double'}, {'name': 'scale_ten', 'type': 'double', 'value': 10.0, 'srcline': 9, 'srcfile': '/home/alok/catkin_ws/src/pid/cfg/Pid.cfg', 'description': 'Scale by 10', 'ctype': 'double', 'cconsttype': 'const double'}, {'name': 'scale_hundred', 'type': 'double', 'value': 100.0, 'srcline': 10, 'srcfile': '/home/alok/catkin_ws/src/pid/cfg/Pid.cfg', 'description': 'Scale by 100', 'ctype': 'double', 'cconsttype': 'const double'}], 'enum_description': 'Scale factor for K setting'}", &PidConfig::Kd_scale)));
//#line 291 "/opt/ros/noetic/lib/python3/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      __min__.Kd = -1.0;
//#line 291 "/opt/ros/noetic/lib/python3/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      __max__.Kd = 1.0;
//#line 291 "/opt/ros/noetic/lib/python3/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      __default__.Kd = 0.1;
//#line 291 "/opt/ros/noetic/lib/python3/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      Default.abstract_parameters.push_back(PidConfig::AbstractParamDescriptionConstPtr(new PidConfig::ParamDescription<double>("Kd", "double", 0, "Kd", "", &PidConfig::Kd)));
//#line 291 "/opt/ros/noetic/lib/python3/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      __param_descriptions__.push_back(PidConfig::AbstractParamDescriptionConstPtr(new PidConfig::ParamDescription<double>("Kd", "double", 0, "Kd", "", &PidConfig::Kd)));
//#line 246 "/opt/ros/noetic/lib/python3/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      Default.convertParams();
//#line 246 "/opt/ros/noetic/lib/python3/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      __group_descriptions__.push_back(PidConfig::AbstractGroupDescriptionConstPtr(new PidConfig::GroupDescription<PidConfig::DEFAULT, PidConfig>(Default)));
//#line 369 "/opt/ros/noetic/share/dynamic_reconfigure/cmake/../templates/ConfigType.h.template"

      for (std::vector<PidConfig::AbstractGroupDescriptionConstPtr>::const_iterator i = __group_descriptions__.begin(); i != __group_descriptions__.end(); ++i)
      {
        __description_message__.groups.push_back(**i);
      }
      __max__.__toMessage__(__description_message__.max, __param_descriptions__, __group_descriptions__);
      __min__.__toMessage__(__description_message__.min, __param_descriptions__, __group_descriptions__);
      __default__.__toMessage__(__description_message__.dflt, __param_descriptions__, __group_descriptions__);
    }
    std::vector<PidConfig::AbstractParamDescriptionConstPtr> __param_descriptions__;
    std::vector<PidConfig::AbstractGroupDescriptionConstPtr> __group_descriptions__;
    PidConfig __max__;
    PidConfig __min__;
    PidConfig __default__;
    dynamic_reconfigure::ConfigDescription __description_message__;

    static const PidConfigStatics *get_instance()
    {
      // Split this off in a separate function because I know that
      // instance will get initialized the first time get_instance is
      // called, and I am guaranteeing that get_instance gets called at
      // most once.
      static PidConfigStatics instance;
      return &instance;
    }
  };

  inline const dynamic_reconfigure::ConfigDescription &PidConfig::__getDescriptionMessage__()
  {
    return __get_statics__()->__description_message__;
  }

  inline const PidConfig &PidConfig::__getDefault__()
  {
    return __get_statics__()->__default__;
  }

  inline const PidConfig &PidConfig::__getMax__()
  {
    return __get_statics__()->__max__;
  }

  inline const PidConfig &PidConfig::__getMin__()
  {
    return __get_statics__()->__min__;
  }

  inline const std::vector<PidConfig::AbstractParamDescriptionConstPtr> &PidConfig::__getParamDescriptions__()
  {
    return __get_statics__()->__param_descriptions__;
  }

  inline const std::vector<PidConfig::AbstractGroupDescriptionConstPtr> &PidConfig::__getGroupDescriptions__()
  {
    return __get_statics__()->__group_descriptions__;
  }

  inline const PidConfigStatics *PidConfig::__get_statics__()
  {
    const static PidConfigStatics *statics;

    if (statics) // Common case
      return statics;

    boost::mutex::scoped_lock lock(dynamic_reconfigure::__init_mutex__);

    if (statics) // In case we lost a race.
      return statics;

    statics = PidConfigStatics::get_instance();

    return statics;
  }

//#line 7 "/home/alok/catkin_ws/src/pid/cfg/Pid.cfg"
      const double Pid_scale_tenth = 0.1;
//#line 8 "/home/alok/catkin_ws/src/pid/cfg/Pid.cfg"
      const double Pid_scale_unity = 1.0;
//#line 9 "/home/alok/catkin_ws/src/pid/cfg/Pid.cfg"
      const double Pid_scale_ten = 10.0;
//#line 10 "/home/alok/catkin_ws/src/pid/cfg/Pid.cfg"
      const double Pid_scale_hundred = 100.0;
}

#undef DYNAMIC_RECONFIGURE_FINAL

#endif // __PIDRECONFIGURATOR_H__
