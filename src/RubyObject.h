#include <node.h>
#include <nan.h>
#include <v8.h>
#include <ruby.h>
#include <map>

class RubyObject : public node::ObjectWrap
{
 public:
  static const char* RUBY_OBJECT_TAG;
  static ID V8_WRAPPER_ID;
 
  static void Init();
  static v8::Local<v8::Function> GetClass(VALUE klass);
  static inline v8::Local<v8::Object> RubyUnwrap(VALUE self)
  {
    VALUE wrappedObj = rb_ivar_get(self, V8_WRAPPER_ID);
    if (wrappedObj == Qnil) {
      return v8::Local<v8::Object>();
    }
    else {
      RubyObject* obj;
      Data_Get_Struct(wrappedObj, RubyObject, obj);
      return NanNew<v8::Object>(*obj->m_owner);
    }
  }
  
  inline VALUE GetObject() { return m_obj; }

 private:
  RubyObject(VALUE obj, v8::Local<v8::Value> owner);
  ~RubyObject();

  static NAN_METHOD(New);
  static NAN_METHOD(CallMethod);

  VALUE m_obj;
  v8::Persistent<v8::Object>* m_owner;
  typedef std::map<ID, v8::Persistent<v8::FunctionTemplate> > TplMap;
  //typedef std::map<ID, v8::CopyablePersistentTraits<v8::FunctionTemplate>::CopyablePersistent> TplMap;
  static TplMap s_functionTemplates;
  static VALUE s_wrappedClass;
};
