using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ClientForCServer
{
    internal interface IClientSimple
    {
        public string IPserver { get; set; }

        public int Port { get; set; }

        void Start();
    }
}
