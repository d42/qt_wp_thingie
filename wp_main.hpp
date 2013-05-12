#include "wp_utils.hpp"
class WpMain:public object_type
{
    Q_OBJECT
        wp_prepare *wp;



    public slots:
        void connect_to_server();
    public:
        WpMain();


};
