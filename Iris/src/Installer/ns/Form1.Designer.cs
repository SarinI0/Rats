namespace ns
{
    partial class Form1

    {

        private System.ComponentModel.IContainer components = null;

        protected override void Dispose(bool disposing)

        {

            if (disposing && (components != null))

            {

                components.Dispose();

            }

            base.Dispose(disposing);

        }
        protected override void SetVisibleCore(bool value)

        {

            if (!this.IsHandleCreated)

            {

                this.CreateHandle();

                value = false;

            }

            base.SetVisibleCore(value);

        }
        #region Windows Form Designer generated code
        private void InitializeComponent()

        {

            this.components = new System.ComponentModel.Container();

            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;

            this.Text = "Form1";

        }
        #endregion

    }

}
